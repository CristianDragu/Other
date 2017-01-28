module TestGraph where

import Graph
import Data.List

{-
    Acesta este modulul de testare pentru acest laborator. Pentru
    a testa un anumit exercitiu decomentati codul corespunzator
    de mai jos si rulati checksN, unde N este numarul execitiului.
    Mai jos aveti si allChecks care verifica toate exercitiile.

    Iata graful pe care se va face testarea:


    +++++              +++++
    + 1 +------------->+ 2 +
    +++++              +++++
      |  |\
      |   \
      |    -------
      |           \
      |            \
      \/            \
    +++++            \ +++++
    + 3 +------------->+ 4 +
    +++++              +++++
      |                  |
      |                  |
      |                  |
      \/                 \/
    +++++              +++++         +++++
    + 5 +------------->+ 6 +-------->+ 7 +
    +++++              +++++         +++++
      |                                /\
      |                                |
      |                                |
      ----------------------------------

-}

testNodes = [1..7]
testArcs = [(1, 2), (1, 3), (3, 4), (4, 1), (3, 5), (5, 6), (4, 6), (5, 7), (6, 7)]


-- 2 --------------------------------------------------------------------------

alGraph = build testNodes testArcs :: AdjListGraph

checks2 = testTemplate "AdjListGraph" alGraph

-- 3 --------------------------------------------------------------------------

aGraph = build testNodes testArcs :: ArcGraph

checks3 = testTemplate "ArcGraph" aGraph

-- 4 --------------------------------------------------------------------------

checks4 = checkAll [
    "Conversion from AdjListGraph to ArcGraph works" ??
        convert alGraph `sameGraph` aGraph,
    "Conversion from ArcGraph to AdjListGraph works" ??
        convert aGraph `sameGraph` alGraph
    ]


-- 5 --------------------------------------------------------------------------

expectedDFSTraversal = [
    (1, Nothing), (2, Just 1), (3, Just 1),
    (4, Just 3), (6, Just 4), (7, Just 6), (5, Just 3)]

checks5 = checkAll [
    "DFS works as expected for AdjListGraph" ??
        dfs alGraph 1 `sameElements` expectedDFSTraversal,
    "DFS works as expected for ArcGraph" ??
        dfs aGraph 1 `sameElements` expectedDFSTraversal
    ]

-- 6 --------------------------------------------------------------------------

expectedBFSTraversal = [
    (1, Nothing), (2, Just 1), (3, Just 1),
    (4, Just 3), (5, Just 3), (6, Just 4), (7, Just 5)]

checks6 = checkAll [
    "BFS works as expected for AdjListGraph" ??
        bfs alGraph 1 `sameElements` expectedBFSTraversal,
    "BFS works as expected for ArcGraph" ??
        bfs aGraph 1 `sameElements` expectedBFSTraversal
    ]
    
-- 7 --------------------------------------------------------------------------
{-
testData = [
    (1, 7, Just [1, 3, 4, 6, 7], Just [1, 3, 5, 7]),
    (3, 2, Just [3, 4, 1, 2], Just [3, 4, 1, 2]),
    (6, 2, Nothing, Nothing)
    ]

checks7 = checkAll [test |  (start, end, dfsPath, bfsPath) <- testData,
                            test <- allTests dfsPath bfsPath start end]
    where
        gTest g gname dfsPath bfsPath start end =
            [mkTest alGraph "AdjListGraph" algo algoName expected start end |
            (algoName, algo, expected) <- [("DFS", dfs, dfsPath), ("BFS", bfs, bfsPath)]]
        allTests dfsPath bfsPath start end =
            gTest alGraph "AdjListGraph" dfsPath bfsPath start end ++
            gTest aGraph "ArcGraph" dfsPath bfsPath start end
        mkTest g gname algo name result start end =
            "Path between " ++ show start ++
            " and " ++ show end ++ " obtained with " ++
            name ++ " on graph type " ++ gname ??
                findPath algo g start end == result
-}
-- All --------------------------------------------------------------------------

-- allChecks = sequence_ [checks2, checks3, checks4, checks5, checks6, checks7]






-- Utilities --------------------------------------------------------------------

testTemplate typeName g = checkAll [
    typeName ++ " gives the correct set of nodes" ??
        nodes g `sameElements` testNodes,
    typeName ++ " gives the correct set of arcs" ??
        arcs g `sameElements` testArcs,
    typeName ++ " implements nodeOut correctly" ??
        nodeOut g 1 `sameElements` [3, 2] &&
        nodeOut g 2 `sameElements` [] &&
        nodeOut g 3 `sameElements` [4, 5] &&
        nodeOut g 5 `sameElements` [6, 7],
    typeName ++ " implements nodeIn correctly" ??
        nodeIn g 6 `sameElements` [4, 5] &&
        nodeIn g 2 `sameElements` [1] &&
        nodeIn g 1 `sameElements` [4],
    typeName ++ " implements arcExists correctly" ??
        and [arcExists g a b | (a, b) <- testArcs]
    ]


data Test = Test {message :: Message, expression :: Bool}

type Message = String

type TestSuite = [Test]

infixl 0 ??

(??) :: Message -> Bool -> Test
message ?? expr = Test message expr

checkAll :: TestSuite -> IO ()
checkAll = mapM_ check

check :: Test -> IO ()
check (Test message expr) = do
  putStr ("Testing: [" ++ message ++ "]...........")
  let outcome = if expr then "PASSED" else "FAILED"
  putStrLn outcome


sameElements :: (Eq a) => [a] -> [a] -> Bool
sameElements xs ys = null (xs \\ ys) && null (ys \\ xs)

sameGraph :: Graph g => g -> g -> Bool
sameGraph g1 g2 = nodes g1 `sameElements` nodes g2 && arcs g1 `sameElements` arcs g2

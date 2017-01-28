module Graph where

import Data.List

{-
    Urmatoarele exercitii vor avea drept scop implementarea unei mici biblioteci
    pentru grafuri ORIENTATE.
    Dupa cum stiti, exista mai multe modalitati de reprezentare a unui graf.
    Biblioteca noastra va defini mai multe astfel de reprezentari, precum
    si algoritmi care opereaza pe grafuri.
    Algoritmii vor fi independenti de reprezentarea interna a grafului - ei
    vor functiona indiferent de ce structura de date am ales noi pentru un anume
    graf.
    Pentru a obtine aceasta genericitate vom abstractiza notiunea de graf intr-o
    clasa care va expune operatiile pe care orice structura de date de tip graf
    ar trebui sa le aiba.
-}

-- reprezentam nodurile ca intregi
type Node = Int

-- reprezentam arcele ca perechi de noduri
type Arc = (Node, Node)

-------------------------------------------------------------------------------

{-
    1.(1.5p) Analizati clasa Graph definita mai jos si scrieti implementarile
    default pentru functiile din aceasta clasa.

    Clasa Graph care defineste interfata pentru toate structurile de grafuri
    pe care le vom defini mai jos.
-}
class Graph g where

    -- Construieste un graf plecand de la o lista de noduri si arcele dintre noduri
    build :: [Node] -> [Arc] -> g

    -- Lista tuturor nodurilor din graf
    nodes :: g -> [Node] -- lista nodurilor din graf

    -- Lista arcelor din graf
    arcs :: g -> [Arc] -- lista muchiilor din graf

    -- lista nodurilor catre care nodul dat ca parametru are un arc
    nodeOut :: g -> Node -> [Node]

    -- lista nodurilor care au un arc catre nodul dat ca parametru
    nodeIn :: g -> Node -> [Node]

    -- verifica daca exista un arc intre 2 noduri
    arcExists :: g -> Node -> Node -> Bool

    -- TODO: implementari default
    arcExists g a b = elem (a, b) (arcs g)
    arcs g = [ (x, y) | x <- (nodes g), y <- (nodes g), (arcExists g x y) ]
    nodeIn g n = [ x | x <- (nodes g), (arcExists g x n)]
    nodeOut g n = [ x | x <- (nodes g), (arcExists g n x)]

-------------------------------------------------------------------------------
{-
    2.(2p) Definiti tipul AdjListGraph care reprezinta un graf ca pe o serie de
    perechi (nod, lista vecini). Includeti AdjListGraph in clasa Graph
-}

data AdjListGraph = AdjList [(Node, [Node])] deriving Show

instance Graph AdjListGraph where
    build nodes arcs = AdjList [ (a, [b | b <- nodes, (a, b) `elem`  arcs]) | a <- nodes ]
    nodes ( AdjList t ) = map fst t  
    arcExists( AdjList l ) a b = b `elem` (snd (head (filter ( \x -> fst x == a ) l )))

-------------------------------------------------------------------------------

{-
    3. (1p) Definiti tipul ArcGraph care reprezinta un graf ca doua lista separate:
    una cu nodurile din graf si una cu arcele din graf.
    Includeti ArcGraph in clasa Graph.
-}

data ArcGraph = A_Graph ([Node], [Arc]) deriving Show

instance Graph ArcGraph where
    build nodes arcs = A_Graph (nodes, arcs)
    nodes ( A_Graph t ) = fst t
    arcs ( A_Graph t ) = snd t 

-------------------------------------------------------------------------------

{-
    4. (0.5p) Definiti functia convert care face conversia intre reprezentari diferite
    de grafuri.
-}
convert :: (Graph g1, Graph g2) => g1 -> g2
convert g = build (nodes g) (arcs g)


-------------------------------------------------------------------------------
{-
    O traversare a unui graf este o lista de perechi (nod, Maybe parinte-node). Aceasta
    structura va contine toate nodurile rezultate in urma unei parcurgeri a unui graf,
    impreuna cu parintele nodului din parcurgere (Pentru un nod N, parintele sau este
    nodul din care s-a ajuns la N in decursul parcurgerii)
-}
type Traversal = [(Node, Maybe Node)]

-- O cale in graf este reprezentata ca lista de noduri din acea cale.
type Path = [Node]

{-
    Definitie pentru algoritmi de parcurgere a unui graf. Un algoritm de parcurgere este o functie
    care primeste un graf si un nod de start si intoarce o structura Traversal. Observati
    ca tipul grafului este o variabila de tip - algoritmii trebuie sa functioneze pentru orice
    structura de graf.
-}
type TraverseAlgo g = g -> Node -> Traversal

-------------------------------------------------------------------------------

{-
    5. (2.5p) Implementati algoritmul de parcurgere in adancime. (Depth-First Search)
-}
dfs :: Graph g => TraverseAlgo g

dfs_helper g [] traversare =  traversare

dfs_helper g (x:xs) traversare
    | elem (fst x) (map fst traversare) = dfs_helper g xs traversare
    | otherwise = dfs_helper g ([(u, Just (fst x)) | u <- (nodeOut g (fst x))] ++ xs) (traversare ++ [x])

dfs g start = dfs_helper g [(start, Nothing)] []

-------------------------------------------------------------------------------

{-
    6. (2.5p) Implementati algoritmul de parcurgere in latime. (Breadth-First Search)
-}
bfs :: Graph g => TraverseAlgo g

bfs_helper g [] traversare =  traversare

bfs_helper g (x:xs) traversare
    | elem (fst x) (map fst traversare) = bfs_helper g xs traversare
    | otherwise = bfs_helper g ( xs ++ [(u, Just (fst x)) | u <- (nodeOut g (fst x))]) (traversare ++ [x])

bfs g start = bfs_helper g [(start, Nothing)] []



-------------------------------------------------------------------------------

{-
    7. (BONUS 1p) Definiti functia findPath care primeste ca parametri:
    * un algoritmi de parcurgere
    * un graf
    * un nod de pornire
    * un nod destinatie
    si care intoarce o cale dintre cele 2 noduri, daca o astfel de cale
    exista.
-}
findPath :: Graph g => TraverseAlgo g -> g -> Node -> Node -> Maybe Path
findPath traverse g n1 n2 = undefined

-------------------------------------------------------------------------------

{-
    8. (BONUS 1p). Creati tipul GenericAdjListGraph care este este similar cu
    AdjListGraph, dar in care nodurile nu sunt neaparat de tip Int - pot
    fi de orice tip.
-}


{-
    9. (BONUS 1p). Adaugati tipul GenericAdjListGraph la clasa Functor
-}

{-
    10. (BONUS 2p). Definiti clasa Listable pentru containere care contin elemente
    si care va avea o singura functie: toList - care intoarce lista elementelor
    continute in container. Adaugati GenericAdjListGraph la aceasta clasa.
-}

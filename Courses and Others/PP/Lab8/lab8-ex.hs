{-# OPTIONS_GHC -F -pgmF htfpp #-}

import Data.List
import Data.Array
import Test.Framework

{-
  1. (2p)
  Având dat tipul de date Vector, definiți funcțiile care calculează distanța
  euclidiană, suma și produsul scalar dintre doi vectori dați.
-}

test_vector :: IO ()
test_vector = do
  assertBool $ eqHelper 2.29128 (distVec v1 v2)
  assertBool $ eqHelperVec (Vector 5 10 5.5) (sumVec v1 v2)
  assertBool $ eqHelper 37.5 (dotProdVec v1 v2)
  where
  eps = 0.01
  eqHelper x y = abs (x - y) <= eps
  eqHelperVec (Vector x1 y1 z1) (Vector x2 y2 z2) =
    eqHelper x1 x2 && eqHelper y1 y2 && eqHelper z1 z2
  v1 = (Vector 2 4 3)
  v2 = (Vector 3 6 2.5)

data Vector = Vector
  { vx :: Double
  , vy :: Double
  , vz :: Double
  } deriving (Show, Eq)

distVec :: Vector -> Vector -> Double
distVec (Vector x1 y1 z1) (Vector x2 y2 z2) = sqrt(((x1 - x2) ^ 2) + ((y1 - y2) ^ 2) + ((z1 - z2) ^ 2)) 

sumVec :: Vector -> Vector -> Vector
sumVec (Vector x1 y1 z1) (Vector x2 y2 z2) = (Vector (x1 + x2) (y1 + y2) (z1 + z2))

dotProdVec :: Vector -> Vector -> Double
dotProdVec (Vector x1 y1 z1) (Vector x2 y2 z2) = ((x1 * x2) + (y1 * y2) + (z1 * z2))

{-
 2. (4p)
  Definiți un tip de date SList a care să aibă funcționalități asemănătoare
  listelor din Scheme, permițând componente la diferite niveluri de imbricare.
  Ex: Lista din Scheme '(1 (3 4) (2)) să poată fi definită în Haskell folosind
  SList.
  Adițional, definiti:
  - emptySList, lista vidă
  - consElem, adaugă un element în capul unei liste
    Ex: consElem 1 '((3 4) (2)) == '(1 (3 4) (2))
  - consList, adaugă o listă (imbricată) în capul unei liste
    Ex: consList '(2 3) '(1 2) == '((2 3) 1 2)
  - headSList, ia primul element dintr-un SList
  - tailSList, ia restul SList-ului
  - deepEqual, o funcție ce verifică egalitatea a două SList
  Notare:
  (1p) definirea tipului de date, emptySList, consElem și consList
  (1p) headSList și tailSList
  (1p) deepEqual
-}

test_slist :: IO ()
test_slist = do
  assertBool $ deepEqual (consElem 2 emptySList)
                         (consList (headSList l1) emptySList)
  assertBool $ deepEqual l2 (tailSList l1)
  where
  l1 = consElem 2 $ consList (consElem 1 $ consElem 1 emptySList) $
       consElem 3 emptySList
  l2 = consList (consElem 1 $ consElem 1 emptySList) $ consElem 3 emptySList

data SList a = Elem a | List [SList a] deriving Show

emptySList :: SList a
emptySList = List []

consElem :: a -> SList a -> SList a
consElem x (List l) = List (Elem x : l) 

consList :: SList a -> SList a -> SList a
consList l (List l2) = List (l : l2)

headSList :: SList a -> SList a
headSList (List l) = head l

tailSList :: SList a -> SList a
tailSList (List l) = (List (tail l))

deepEqual :: Eq a => SList a -> SList a -> Bool
deepEqual (Elem x) (Elem y) = x == y
deepEqual (List []) (List []) = True
deepEqual (List l1) (List l2) = deepEqual (headSList (List l1)) (headSList (List l2)) && deepEqual (tailSList (List l1)) (tailSList (List l2))

{-
  3. (4p)
  Definiti un tip de date BST a pentru a implementa un arbore binar de cautare.
  De asemenea, definiti functii pentru a crea un arbore binar de cautare de la
  o lista de elemente, cautarea unui element intr-un arbore binar de cautare si
  o functie care intoarce lista elementelor din parcurgerea in preordine a
  arborelui.

  Hint: Este de preferat ca arborele binar de cautare sa fie balansat, lucru
  usor de obtinut la creare daca lista de elemente este sortata
-}

test_bst :: IO ()
test_bst = do
  assertEqual (Just 1) $ findElem bst 1
  assertEqual [3,2,1,4] $ preorder bst
  where
  bst = makeBST [2,3,1,4]


data BST a = EmptyBST | LeafBST a | ConsBST a (BST a) (BST a) deriving Show

makeBST :: Ord a => [a] -> BST a
makeBST list = if list == [] then EmptyBST else ConsBST val (makeBST stanga) (makeBST dreapta)
    where
    sortedList = sort list
    val = sortedList !! (div (length sortedList) 2)
    stanga = take (div (length sortedList) 2) sortedList
    dreapta = drop ((div (length sortedList) 2) + 1) sortedList

findElem :: (Ord a, Eq a) => BST a -> a -> Maybe a
findElem EmptyBST a = Nothing
findElem (ConsBST x bstL bstR) a = if (x == a) then Just a
                                  else if (a < x) then findElem bstL a
                                  else findElem bstR a

preorder :: BST a -> [a]
preorder EmptyBST = []
preorder (ConsBST x bstL bstR) = [x] ++ preorder bstL ++ preorder bstR

{-
  4. (BONUS, 2p)
  Având dat tipul BinaryTree a din cadrul exercițiilor rezolvate, definiți
  funcția subtree, care verifică dacă arborele t1 este un subarbore al
  arborelui t2.
  Ex: subtree (makeBinTree [1,2]) (makeBinTree [1,2,3,4]) == True
-}

test_subtree :: IO ()
test_subtree = do
  assertBool $ subtree (Leaf 1) t
  assertBool $ subtree (makeBinTree [1,2]) t
  assertBool $ subtree (makeBinTree [3,4]) t
  assertBool $ not $ subtree (makeBinTree [2,3]) t
  where
  t = makeBinTree [1,2,3,4]

data BinaryTree a = Node (BinaryTree a) (BinaryTree a) | Leaf a deriving Show

makeBinTree :: [a] -> BinaryTree a
makeBinTree lst = head $ mergeUpwards leafList
    where
      leafList = map (\x -> Leaf x) lst
      mergeUpwards [] = []
      mergeUpwards [x] = [x]
      mergeUpwards (x:y:xs) = mergeUpwards ( (Node x y) : mergeUpwards xs)

subtree :: Eq a => BinaryTree a -> BinaryTree a -> Bool
subtree = undefined

{-
  5. (BONUS, 3p)
  Implementați o tabelă de dispersie, i.e. un vector de lungime fixă de
  „bucket”-uri, fiecare „bucket” conținând o listă de elemente având un tip
  arbitrar. Adăugarea elementelor în tabela de dispersie va fi făcută după o
  funcție de dispersie având tipul HashFunc a: aplicarea funcției de dispersie
  asupra elementului va da indexul „bucket”-ului unde va fi adăugat acesta.

  Vor fi implementate tipul de date HashTable a, tabela vidă emptyH și
  funcțiile insertH și findH, pentru inserarea și respectiv regăsirea
  elementelor în tabelă. Dorim să accesăm „bucket”-urile în O(1), motiv pentru
  care se cere folosirea tipului Array din modulul Data.Array. Pentru n
  „bucket”-uri, indexarea va fi făcută de la 0 la n - 1.

  Funcțiile relevante din Data.Array sunt: array (inițializare), (//)
  (actualizare), (!) (indexare).
  http://hackage.haskell.org/package/array-0.5.0.0/docs/Data-Array.html#t:Array

  Atenție, o tabelă va fi definită pe baza structurii propriu-zise și a
  funcției de dispersie, motiv pentru care funcția de dispersie *trebuie* să
  fie parte din definiția tipului de date.

  Mai multe detalii la:
  https://en.wikipedia.org/wiki/Hash_table
-}

test_hash :: IO ()
test_hash = do
  let hf = (`mod` nb) . length
      nb = 3
      h1 = emptyH nb hf
      h2 = insertH "abc" $ insertH "d" $ insertH "ef" h1
      h3 = insertH "ghci" h2
  assertEqual Nothing $ findH "d" h1
  assertEqual (Just "d") $ findH "d" h2
  assertEqual (Just "abc") $ findH "abc" h2
  assertEqual (Just "ef") $ findH "ef" h2
  assertEqual (Just "ghci") $ findH "ghci" h3

type HashFunc a = a -> Int
data HashTable a = UndefinedHashTable

-- emptyH numar_bucketuri functie_hash
emptyH :: Int -> HashFunc a -> HashTable a
emptyH = undefined

insertH :: a -> HashTable a -> HashTable a
insertH = undefined

findH :: Eq a => a -> HashTable a -> Maybe a
findH = undefined

-- functie auxiliara, utila pentru afisarea HashTable
showHT :: Show a => HashTable a -> String
showHT = undefined

runTests :: IO ()
runTests = htfMain htf_thisModulesTests

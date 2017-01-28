{-
  Definirea tipului Punct folosind type
  In acest caz tipul de date pentru
  perechea care formeaza punctul trebuie
  definite la creare
-}

type Punct = (Int, Int)

manhattanDistance :: Punct -> Punct -> Int
manhattanDistance p1 p2 = difX + difY
  where
    difX = abs (x1 - x2)
    difY = abs (y1 - y2)
    (x1, y1) = p1
    (x2, y2) = p2

{-
 - Newtype
 -}

{-
  Definirea tipurilor Celsius si Fahrenheit
  impreuna cu functiile de conversie
-}

newtype Celsius = MakeCelsius Float deriving Show

newtype Fahrenheit = MakeFahrenheit Float deriving Show

fah2cel :: Fahrenheit -> Celsius
fah2cel (MakeFahrenheit x) = MakeCelsius ((5 / 9) * (x - 32))

cel2fah :: Celsius -> Fahrenheit
cel2fah (MakeCelsius x) = MakeFahrenheit (x * 9 / 5 + 32)

{-
  Se observa ca pentru a defini functiile de conversie
  se descompune tipul de date primit. In primul caz
  elementul de tip Fahrenheit se descompune in MakeFahrenheit x
  si se foloseste valoare x in calcule, urmand ca valoarea
  calculata pentru celsius sa fie pasata constructorului
  MakeCelsius, functia avand ca rezultat un element de tip
  Celsius
-}

{-
  newtype poate fi parametrizat insa constructorul sau primeste
  un singur parametru. Asa ca in construirea tipului Pair folosind
  newtype si tipurile a si b constructorul primeste un singur
  argument, o pereche de tipurile a si b
-}
newtype PairT a b = PairC (a,b) deriving Show

fstPair (PairC p) = fst p
sndPair (PairC p) = snd p


{-
 - Data
 -}

{-
  Tipuri inregistrare
-}

{-
  Folosirea tipurilor inregistrare.
  Avand tipul de date Student cu constructorul Student,
  care primeste 3 parametri String String Int, definit
  ca tip inregistrare se poate observa utilizarea
  functiilor de extractie a datelor definite ca si
  campuri ale tipului
-}

data Student = Student { nume :: String
             , prenume :: String
             , varsta :: Int
             } deriving Show
{-
  Pentru a folosi o instanta de tipul Student
  aceasta se poate construi prin furnizarea datelor de tipurile
  corespunzatoare constructorului
  In consola ghci se ruleaza:
   :t nume
   :t prenume
   :t varsta
   nume (Student "Ion" "Ionut" 23)
   prenume (Student "Ion" "Ionut" 23)
   varsta (Student "Ion" "Ionut" 23)
-}

{-
  Tipuri enumerare
-}

data Zi = Luni | Marti | Miercuri | Joi | Vineri | Sambata | Duminica deriving Show

nrCeasuriRele zi = case zi of
          Marti -> 3
          otherwise -> 0


{-
  Tipuri parametrizate
-}

data Vector a = Vector a a a deriving Show

vectPlus :: (Num a) => Vector a -> Vector a -> Vector a
vectPlus (Vector x y z) (Vector i j k) = Vector (x + i) (y + j) (k + z)

scalarMult :: (Num a) => Vector a -> a -> Vector a
scalarMult (Vector x y z) m = Vector (x * m) (y * m) (z * m)


{-
  In unele cazuri se doreste anuntarii unui esec in evaluarea
  functiei. Pentru acest lucru exista Maybe.
-}

-- data Maybe a = Just a | Nothing deriving Show

{-
  Tipul Maybe a reprezinta tipul rezultatului evaluarii, acesta
  fiind Just a, in cazul in care evaluarea s-a efectuat cu succes
  sau Nothing in caz contrar. De retinut a este o variabila de tip
  si in cazul intoarcerii cu succes Just va fi acompaniat de valoarea
  ce are tipul a
-}

{-
  Functia myHead va returna Nothing in cazul in care lista este vida si
  incercarea de a luat capul listei nu se poate efectua. In cazul in care
  lista contine cel putin un element se intoarce Just x
-}
myHead [] = Nothing
myHead (x:_) = Just x

{-
  In cazul in care se doreste rezultatele unor functii care intorc Maybe
  pentru a le utiliza se poate proceda folosind pattern match sau case
-}

sumHeadLists fstList sndList = case myHead fstList of
                Nothing -> Nothing
                Just x -> case myHead sndList of
                      Nothing -> Nothing
                      Just y -> Just (x + y)

{-
  Tipuri de date recursive
-}

{-
  Tipul numerelor naturale definit recursiv.
  Ex: numarul 0 este Zero iar celelalte vor fi
  aplicari ale constructorului Succ asupra lui Zero
-}

data Natural = Zero | Succ Natural deriving Show

-- Pentru a trece un numar natural in Natural se fac apeluri recursive pana la 0
toNatural :: Int -> Natural
toNatural 0 = Zero
toNatural x = Succ (toNatural $ x - 1)

-- Pentru a trece un Natural in numar natural se fac apeluri recursive pana la Zero
toInt :: Natural -> Int
toInt Zero = 0
toInt (Succ x) = 1 + (toInt x)


{-
  Pentru a declara tipul de date arbore binar de tipul a in care valorile sunt
  tinute in frunze. Pentru a retine valorile in toate nodurile tipul de date
  trebuie modificat
-}

data BinaryTree a = Node (BinaryTree a) (BinaryTree a) | Leaf a deriving Show

{-
  makeTree primeste o lista de numere si va intoarce arborele binar cu numerele
  respective in frunze

  In cazul in care se trimite o lista vida va da esec, intrucat arborele nu
  permite arbore vid
-}

makeBinTree :: [a] -> BinaryTree a
makeBinTree lst = head $ mergeUpwards leafList
    where
      leafList = map (\x -> Leaf x) lst
      mergeUpwards [] = []
      mergeUpwards [x] = [x]
      mergeUpwards (x:y:xs) = mergeUpwards ( (Node x y) : mergeUpwards xs)

{-
 - Tipul de date list
 -}

{-
  Tipul de date TList reprezinta tipul lista reprezentativ
  pentru limbaje functionale. Este format din constructorul Nil pentru
  terminarea liste si constructorul de concatenare.
-}
data TList a = Cons a (TList a) | Nil deriving Show

{-
  tlistToList transforma o TList intr-o lista Haskell
-}
tlistToList :: TList a -> [a]
tlistToList Nil = []
tlistToList (Cons x y) = x : tlistToList y

{-
  listToTList transforma o TList intr-o lista Haskell
-}
listToTList :: [a] -> TList a
listToTList [] = Nil
listToTList (x:xs) = Cons x (listToTList xs)



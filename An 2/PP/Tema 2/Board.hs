{-
    Tabla de joc și mutările posibile.

    Modulul exportă numai funcțiile enumerate mai jos, ceea ce înseamnă
    că doar acestea vor fi vizibile din alte module. Justificarea vizează
    prevenirea accesului extern la structura obiectelor 'Board', și a eventualei
    coruperi a consistenței interne a acestora.
-}
module Board
    ( Board
    , Player (..)  -- Exportăm și constructorii de date 'You' și 'Opponent'.
    , House
    , build
    , yourSeeds
    , oppsSeeds
    , who
    , isOver
    , initialBoard
    , move
    , scores
    , successors
    ) where

import Consecutive

{-
    Jucătorul care urmează să mute.
-}
data Player = You | Opponent deriving (Eq, Show)

{-
    Tipul caselor, definit pentru lizibilitate.
-}
type House = Int

{-
    *** TODO ***

    Definiți tipul 'Board', astfel încât să rețină informație despre starea
    jocului, inclusiv tabla de joc.

    Observați că viitorii constructori de date și eventualele câmpuri pe care
    le veți specifica nu vor apărea în lista de funcții exportate de modul
    (vezi explicația de la începutul fișierului).
-}
data Board = Board Player House House House House House House House House House House House House House House deriving Eq

{-
    *** TODO ***

    Instanțiați clasa 'Show' cu tipul 'Board'. Exemplu de reprezentare,
    unde scorurile sunt aferent jucătorilor 'You', respectiv 'Opponent':

       4  4  4  4  4  4
     0                  0    Next: You, Playing, Score: (0,0)
       4  4  4  4  4  4
-}

instance Show Board where
    show (Board player c1 c2 c3 c4 c5 c6 c7 c8 c9 c10 c11 c12 c13 c14) = 
        "  " ++ show c8 ++ "  " ++ show c9 ++ "  " ++ show c10 ++ "  " ++ show c11 ++ "  " ++ show c12 ++ "  " ++ show c13 ++ "\n" ++ show c14 ++ "                   " ++ show c7 ++ "\n" ++ "  " ++ show c1 ++ "  " ++ show c2 ++ "  " ++ show c3 ++ "  " ++ show c4 ++ "  " ++ show c5 ++ "  " ++ show c6 ++ "\n"

{-
    *** TODO BONUS ***

    Instanțiați clasa 'Consecutive', pentru a putea determina dacă în două
    configurații ale tablei trebuie să mute același jucător.
-}
instance Consecutive Board where
    b1 >< b2 = undefined

{-
    *** TODO ***

    Construiește tabla de joc.

    Funcția trebuie să determine dacă jocul este deja încheiat, pe baza
    conținutului caselor.
-}
build :: ([Int], Int)  -- Conținutul caselor și al depozitului utilizatorului
      -> ([Int], Int)  -- Conținutul caselor și al depozitului adversarului
      -> Player        -- Jucătorul aflat la rând
      -> Board         -- Tabla construită
build ([c1, c2, c3, c4, c5, c6], c7) ([c8, c9, c10, c11, c12, c13], c14) player = (Board player c1 c2 c3 c4 c5 c6 c7 c8 c9 c10 c11 c12 c13 c14)

{-
    *** TODO ***

    Întoarce conținutul caselor și al depozitului utilizatorului.
-}
yourSeeds :: Board -> ([Int], Int)
yourSeeds (Board player c1 c2 c3 c4 c5 c6 c7 c8 c9 c10 c11 c12 c13 c14) = ([c1, c2, c3, c4, c5, c6], c7)

{-
    *** TODO ***

    Întoarce conținutul caselor și al depozitului adversarului.
-}
oppsSeeds :: Board -> ([Int], Int)
oppsSeeds (Board player c1 c2 c3 c4 c5 c6 c7 c8 c9 c10 c11 c12 c13 c14) = ([c8, c9, c10, c11, c12, c13], c14)

{-
    *** TODO ***

    Întoarce jucătorul aflat la rând.
-}
who :: Board -> Player
who (Board player c1 c2 c3 c4 c5 c6 c7 c8 c9 c10 c11 c12 c13 c14) = player

{-
    *** TODO ***

    Întoarce 'True' dacă jocul s-a încheiat.
-}
isOver :: Board -> Bool
isOver (Board player c1 c2 c3 c4 c5 c6 c7 c8 c9 c10 c11 c12 c13 c14) = if (c1 + c2 + c3 + c4 + c5 + c6 == 0) || (c8 + c9 + c10 + c11 + c12 + c13 == 0)
    then True
    else False

{-
    *** TODO ***

    Tabla inițială.
-}
initialBoard :: Board
initialBoard = build (replicate 6 4, 0) (replicate 6 4, 0) You

{-
    *** TODO ***

    Realizează o mutare pornind de la casa furnizată ca parametru, în funcție
    de configurația actuală a tablei și de jucătorul aflat la rând.

    Întoarce aceeași configurație dacă mutarea nu poate fi efectuată
    din diverse motive, precum numărul eronat al casei, sau casa goală.
-}

-- In functie de jucatorul actual, este intors urmatorul jucator
schimbJucator player = 
    if (player == You)
        then Opponent
        else You

-- Metoda care schimba valoarea de pe o anumita pozitie din vector
inlocuie vec val poz ind =
 if (vec == [])
  then []
  else if (ind == poz)
   then [val] ++ (inlocuie (tail vec) val poz (ind + 1))
   else [(head vec)] ++ (inlocuie (tail vec) val poz (ind + 1))

-- Metoda care returneaza valoarea de pe o pozitie din vector
getVal vec poz ind = 
    if (vec == [])
        then -2
        else if (ind == poz)
            then (head vec)
            else getVal (tail vec) poz (ind + 1)

-- Metoda care aduna doua valori la baza tablei (in casa mea de puncte sunt depozitate
-- pietricelele capturate)
depoziteazaValori vec ind baza val1 val2 = 
    if(vec == [])
        then []
        else if (ind == baza)
            then [(head vec) + val1 + val2] ++ (tail vec)
            else [(head vec)] ++ (depoziteazaValori (tail vec) (ind + 1) baza val1 val2)

-- Metoda care "captureaza" pietrele din casutele inamicului si apoi le depunde in 
-- baza mea, impreuna cu pitrele din casutele mele corespondente.
capturare vec baza val1 pozVal2 = do
    let val2 = getVal vec pozVal2 1
    let aux = inlocuie vec 0 pozVal2 1
    depoziteazaValori aux 1 baza val1 val2

{- Metoda care muta pietrele in casute.
    houses = vectorul meu cu casutele ce trebuiesc parcurse cand se muta pietrele.
    val = valoarea initiala de pietre care au fost luate din casuta aleasa pentru mutare
    start = pozitia de inceput a vectorului
    ind = indice pentru pozitia actuala in vector

    Mentiuni:
    Exemplu tabla de joc:
        0 1 0 0 0 0
    0                 0
       19 1 1 1 1 1
            |
    
    Daca poz este situat pe casuta marcata cu linie, atunci vectorul meu houses va 
    fi de forma: 1 1 1 0 0 0 0 1 0 19 1 1 (pleaca de la pozitia de start si merge 
    circular pe tabla de joc).

    Metoda parcurge vectorul in mod recursiv, punand pietrele in casute.
    Pietrele sunt puse in casute doar intr-o parcurgere a vectorului, folosind formula: 
    valoareDinCasa + [valPietreActualeRamase / 14] + 1

    Baza mea are formula: 7 - start.
-}

adaugaPietre houses val start ind =
    if(val == 0 || ind > (length houses))
        then houses
        else if (val == 0) 
            then adaugaPietre houses val start ind
            else if (val /= 1)
                then adaugaPietre (inlocuie houses ( (getVal houses ind 1) + (val `div` 14) + 1 ) ind 1) (val - 1) start (ind + 1)
                else
                    if (ind == (7 - start))
                        then do
                            let val1 = getVal houses ind 1
                            adaugaPietre (inlocuie houses ( val1 + (val `div` 14) + 1 ) ind 1) (val - 1) start (ind + 1)
                        else if ( (ind < (7 - start)) && ((getVal houses ((2 * (7 - start)) - ind) 1) /= 0) && ((getVal houses ind 1) == 0) )
                            then do
                                let val1 = getVal houses ind 1
                                capturare (inlocuie houses 0 ind 1) (7 - start) ( val1 + (val `div` 14) + 1 ) ((2 * (7 - start)) - ind)
                            else do
                                let val1 = getVal houses ind 1
                                if ( (ind > ((7 - start) + 6)) && ((getVal houses (((2 * ((7 - start) + 6)) - ind) + 1) 1) /= 0) && (val1 == 0) )
                                    then capturare (inlocuie houses 0 ind 1) (7 - start) 1 (((2 * ((7 - start) + 6)) - ind) + 1)
                                    else adaugaPietre (inlocuie houses ( val1 + (val `div` 14) + 1 ) ind 1) (val - 1) start (ind + 1)

-- Metoda move care se foloseste de metodele de mai sus pentru a realiza o mutare
-- Am folosit variabile cu nume sugestive pentru a se intelege mai usor ideea de 
-- rezolvare.
-- In cazul in care este la mutare oponentul, ROTESC tabla de joc pentru a putea
-- folosi functiile de mai sus.
-- Jucatorul care urmeaza sa execute urmatoarea mutare este dat de formulele:
--   ((7 - h) + val) `mod` 13 == 7, in cazul in care muta oponentul acum
--   (h + val) `mod` 13 == 7, daca You muta in momentul actual.

move :: House -> Board -> Board
move h (Board player c1 c2 c3 c4 c5 c6 c7 c8 c9 c10 c11 c12 c13 c14) = do
    if(h < 1 || h > 6)
        then build ([c1,c2,c3,c4,c5,c6],c7) ([c8,c9,c10,c11,c12,c13],c14) player
        else
        if ( player == Opponent ) then do
            let tabla = (Board player c13 c12 c11 c10 c9 c8 c14 c6 c5 c4 c3 c2 c1 c7)
            let val = getVal (fst (yourSeeds tabla)) (7 - h) 1
            if (val /= 0)
                then do
                    let myHouses = (fst (yourSeeds tabla))
                    let oppHouses = (fst (oppsSeeds tabla))
                    let myBase = (snd (yourSeeds tabla))
                    let oppBase = (snd (oppsSeeds tabla))
                    let aux = inlocuie myHouses 0 (7 - h) 1
                    let myHouses = aux
                    let casute = myHouses ++ [myBase] ++ (reverse oppHouses)
                    let houses = take 13 ( drop (7 - h) (cycle casute) )
                    let aux = adaugaPietre houses val (7 - h) 1
                    let myHouses = take 6 (drop h aux)
                    let oppHouses = reverse (drop (13 - (7 - h)) aux ++ (take (6 - (7 - h)) aux))
                    let oppBase = head (drop (6 - (7 - h)) aux)
                    let myBase = (snd (yourSeeds tabla))
                    if(((7 - h) + val) `mod` 13 == 7)
                        then build (myHouses, c7) (oppHouses, oppBase) player
                        else build (myHouses, c7) (oppHouses, oppBase) (schimbJucator player)
            else build ([c1,c2,c3,c4,c5,c6],c7) ([c8,c9,c10,c11,c12,c13],c14) player
        else do
            let tabla = (Board player c1 c2 c3 c4 c5 c6 c7 c8 c9 c10 c11 c12 c13 c14)
            let val = getVal (fst (yourSeeds tabla)) h 1
            if (val /= 0)
                then do
                    let myHouses = (fst (yourSeeds tabla))
                    let oppHouses = (fst (oppsSeeds tabla))
                    let myBase = (snd (yourSeeds tabla))
                    let oppBase = (snd (oppsSeeds tabla))
                    let aux = inlocuie myHouses 0 h 1
                    let myHouses = aux
                    let casute = myHouses ++ [myBase] ++ (reverse oppHouses)
                    let houses = take 13 ( drop h (cycle casute) )
                    let aux = adaugaPietre houses val h 1
                    let myHouses = drop (13 - h) aux ++ take (6 - h) aux
                    let oppHouses =  reverse (take 6 (drop (7 - h) aux))
                    let myBase = head ( drop (6 - h) aux)
                    if((h + val) `mod` 13 == 7)
                        then build (myHouses, myBase) (oppHouses, oppBase) player
                        else build (myHouses, myBase) (oppHouses, oppBase) (schimbJucator player)
            else build ([c1,c2,c3,c4,c5,c6],c7) ([c8,c9,c10,c11,c12,c13],c14) player

{-
    *** TODO ***

    Întoarce scorurile (utilizator, adversar).

    Calculul trebuie să țină cont de eventuala încheiere a jocului.
-}
scores :: Board -> (Int, Int)
scores (Board player c1 c2 c3 c4 c5 c6 c7 c8 c9 c10 c11 c12 c13 c14) = if (c1 + c2 + c3 + c4 + c5 + c6 == 0) || (c8 + c9 + c10 + c11 + c12 + c13 == 0) 
                                                                            then (c1 + c2 + c3 + c4 + c5 + c6 + c7, c8 + c9 + c10 + c11 + c12 + c13 + c14)
                                                                        else (c7, c14)

{-
    *** TODO ***

    Întoarce perechile casă-configurație, reprezentând mutările care pot fi
    făcute într-un singur pas, pornind de la configurația actuală.
-}

successors :: Board -> [(House, Board)]
successors (Board player c1 c2 c3 c4 c5 c6 c7 c8 c9 c10 c11 c12 c13 c14) = do
    let tabla = (Board player c1 c2 c3 c4 c5 c6 c7 c8 c9 c10 c11 c12 c13 c14)
    [ (x, y) | x <- [1..6], y <- [(move x tabla)], ( (yourSeeds y) /= (yourSeeds tabla) ) || ( (oppsSeeds y) /= (oppsSeeds tabla) ) ]

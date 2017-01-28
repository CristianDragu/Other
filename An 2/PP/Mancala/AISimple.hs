module AISimple where

import Board
import Interactive

{-
    *** TODO ***

    Întoarce tabla rezultată din aplicarea acelei mutări care maximizează
    scorul adversarului.
-}

findMax perechi ind perecheMax = 
	if (ind >= length perechi)
		then perecheMax
		else if (snd (scores (snd (perechi !! ind))) > snd (scores (snd perecheMax)))
			then findMax perechi (ind + 1) (perechi !! ind)
			else findMax perechi (ind + 1) perecheMax

-- Ma folosesc de lista returnata de functia successors pentru a gasi mutarea dorita
step :: Board -> (House, Board)
step tabla = do
	let succesori = successors tabla
	if ( (length succesori) == 1 )
		then succesori !! 0
		else findMax succesori 1 (succesori !! 0)

{-
    Urmărește pas cu pas evoluția jocului, conform strategiei implementate.
-}
userMode :: IO ()
userMode = humanVsAI step

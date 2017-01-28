% Tudor Berariu (C) 2015 <tudor.berariu@gmail.com>

% Povestea (inspiratÄƒ de È˜tirile de la Ora 5)
%
% ÃŽn liniÈ™titul nostru oraÈ™ s-a produs o crimÄƒ. Un individ a pÄƒtruns
% Ã®n casa unui bÄƒtrÃ¢n È™i l-a ucis. Cadravrul a fost ascuns de cÄƒtre
% criminal È™i nu este de gÄƒsit. Este un caz complicat, dar doi
% detectivi, D1 È™i D2, fac cercetÄƒri È™i au deja o listÄƒ de
% suspecÈ›i. È˜tiu despre fiecare dintre aceÈ™tia ce maÈ™inÄƒ are È™i care
% este arma lui preferatÄƒ.
%
% Pentru a rezolva cazul trebuie sÄƒ afle cu ce armÄƒ a fost ucisÄƒ
% victima È™i cu ce maÈ™inÄƒ a fugit criminalul. Din fericire, dacÄƒ se
% poate vorbi despre aÈ™a ceva Ã®n cazul unei crime Ã®ngrozitoare, nu
% existÄƒ doi suspecÈ›i care sÄƒ aibÄƒ aceeaÈ™i maÈ™inÄƒ È™i aceeaÈ™i armÄƒ.
%
% Cei doi detectivi se Ã®ntÃ¢lnesc la secÈ›ie. D1 s-a Ã®ntÃ¢lnit cu un
% martor È™i a aflat cu ce maÈ™inÄƒ a fugit criminalul. D2 a gÄƒsit arma
% crimei. Cei doi se Ã®ntÃ¢lnesc la secÈ›ie, unde au urmÄƒtorul dialog pe
% care tu Ã®l asculÈ›i indiscret.
%
% D1: È˜tiu cÄƒ nu È™tii cine-i criminalul. Nici eu nu È™tiu.
% D2: ÃŽncÄƒ nu È™tiu cine este.
% D1: Nici eu nu È™tiu Ã®ncÄƒ cine este criminalul.
% D1: Acum mi-am dat seama.
% D2: Mi-am dat seama È™i eu.
%
% Cine este criminalul?

% ----------------------------------------------------------------------------
% MaÈ™ini

conduce(aurel, ford).
conduce(bogdan, bmw).
conduce(cosmin, bmw).
conduce(daniel, ford).
conduce(eugen, bmw).
conduce(florin, dacia).
conduce(george, fiat).
conduce(horia, audi).
conduce(irina, dacia).
conduce(jean, fiat).
conduce(kiki, audi).
conduce(laura, seat).
conduce(marian, mercedes).
conduce(nicodim, opel).
conduce(ovidiu, honda).
conduce(paul, honda).

% Arme

inarmat(aurel, sabie).
inarmat(bogdan, pistol).
inarmat(cosmin, arbaleta).
inarmat(daniel, grenada).
inarmat(eugen, grenada).
inarmat(florin, sabie).
inarmat(george, pistol).
inarmat(horia, arbaleta).
inarmat(irina, pusca).
inarmat(jean, cutit).
inarmat(kiki, prastie).
inarmat(laura, pusca).
inarmat(marian, cutit).
inarmat(nicodim, prastie).
inarmat(ovidiu, maceta).
inarmat(paul, mitraliera).

% ----------------------------------------------------------------------------
% 1. (0.5p) ScrieÈ›i un predicat suspect(Nume:Masina:Arma) care sÄƒ fie
% adevÄƒrat pentru fiecare suspect al problemei noastre.

suspect(Nume:Masina:Arma) :-
    conduce(Nume, Masina),
    inarmat(Nume, Arma).

% ----------------------------------------------------------------------------
% 2. (0.5p) ScrieÈ›i un predicat au_bmw(ListaNume) care sÄƒ fie adevÄƒrat
% atunci cÃ¢nd ListaNume este lista cu numele tuturor celor care au
% bmw.  FolosiÈ›i setof/1.

au_bmw(ListaNume) :- 
    setof(X, conduce(X, bmw), ListaNume).

% ----------------------------------------------------------------------------
% 3. (0.5p) ScrieÈ›i un predicat au_masina(Marca, ListaNume) care sÄƒ
% fie adevÄƒrat atunci cÃ¢nd ListaNume este lista cu numele tuturor
% celor care au masina de tipul Marca. FolosiÈ›i setof/1.

au_marca(Masina, ListaNume) :-
    setof(X, conduce(X, Masina), ListaNume).

% ----------------------------------------------------------------------------
% 4. (0.5p) ScrieÈ›i un predicat arme_bmw(ListaArme) care sÄƒ fie adevÄƒrat
% atunci cÃ¢nd ListaArme reprezinta multimea tuturor armelor detinute
% de conducatori de bmw.  FolosiÈ›i setof/1.

arme_bmw(ListaArme) :-
    setof(Y, X^(conduce(X, bmw), inarmat(X, Y)), ListaArme).

% ----------------------------------------------------------------------------
% 5. (0.5p) ScrieÈ›i un predicat arme_marca(Marca, ListaArme) care sÄƒ
% fie adevÄƒrat atunci cÃ¢nd ListaArme reprezinta multimea tuturor
% armelor detinute de conducatori de masini tipul Marca.  FolosiÈ›i
% setof/1.

arme_marca(Marca, ListaArme) :-
    setof(Y, X^(conduce(X, Marca), inarmat(X, Y)), ListaArme).

% ----------------------------------------------------------------------------
% 6. (0.5pp) Scrie un predicat marci_arma_unica/1 care sÄƒ afiÈ™eze lista
% maÈ™inilor pentru care lista armelor pe care le deÈ›in conducÄƒtorii
% unei mÄƒrci conÈ›ine un singur element. Hint: folosiÈ›i-vÄƒ de
% rezolvarea exerciÈ›iului 5.  Nu folosiÈ›i length/2.

marci_arma_unica(Marci) :-
    setof(Marca, X^(arme_marca(Marca, [X])), Marci).

% ----------------------------------------------------------------------------
% ----------------------------------------------------------------------------

% SÄƒ revenim la secÈ›ie de poliÈ›ie unde tu tragi cu urechea la dialogul
% dintre cei doi detetivi:
% 
% Prima replicÄƒ:
% Detectiv A : È˜tiam cÄƒ nu È™tii cine-i criminalul.
%
% Ce Ã®nseamnÄƒ asta? Detectivul A È™tie maÈ™ina cu care a fugit
% suspectul. AceastÄƒ marcÄƒ de maÈ™inÄƒ este condusÄƒ de suspecÈ›i care
% mÃ¢nuiesc diferite arme. DacÄƒ mÄƒcar una dintre aceste arme ar fi
% aparÈ›inut doar unui singur suspect, atunci Detectivul B ar fi putut
% È™ti care este soluÈ›ia acestui caz.
%
% Ce soluÈ›ii eliminÄƒm?
%
% DacÄƒ Detectivul A ar fi aflat cÄƒ adevÄƒratul criminal a condus o
% Honda, atunci ar fi existat douÄƒ soluÈ›ii posibile:
%
% ovidiu - honda - maceta
% ovidiu - paul - mitraliera
%
% Dar cum nu existÄƒ decÃ¢t un singur individ care are macetÄƒ (Ovidiu),
% Detectivul A nu ar fi putut afirma cÄƒ Detectivul B nu poate È™ti.
%
% honda nu este, deci o soluÈ›ie
%
% Trebuie eliminate toate maÈ™inile care sunt "Ã®n pereche" cu arme
% pentru care nu existÄƒ mai multe posibilitÄƒÈ›i.

% ----------------------------------------------------------------------------
% 7. (2p) Scrie un predicat suspect1/1 care este adevÄƒrat doar pentru
% numele suspectilor care respectÄƒ condiÈ›ia impusÄƒ de replica
% Detectivului A.

marca_arme(Arma, Marci) :-
    setof(Marca, Nume^(conduce(Nume, Marca), inarmat(Nume, Arma)), Marci).

arme_marca_unica(Arme) :-
    setof(Arma, Marci^(marca_arme(Arma, [Marci])), Arme).

suspect1(Nume:Masina:Arma):-
    suspect(Nume:Masina:Arma),
    \+ (arme_marca_unica(Arme), member(Arma, Arme), marca_arme(Arma, Marci), member(Masina, Marci)).

% ----------------------------------------------------------------------------
% A doua replicÄƒ:
%
% Detectivul A: Nici eu nu È™tiu!
%
% 8. (2p) Scrie un predicat suspect2/1 care este adevÄƒrat doar pentru
% numele suspecÈ›ilor care respectÄƒ condiÈ›ia impusÄƒ de replica
% Detectivului A.
%
% AtenÈ›ie: informaÈ›ia ce trebuie filtratÄƒ acum este cea care
% corespunde primei replici.

suspect2(Nume:Masina:Arma):-
    suspect1(Nume:Masina:Arma),
    suspect1(Nume1:Masina:_),
    Nume \= Nume1.

% ----------------------------------------------------------------------------
% A treia replicÄƒ:
%
% Detectivul B: Nici eu nu È™tiu!
%
% 9. (2p) Scrue un predicat suspect3/1 care este adevÄƒrat doar pentru
% numele suspecÈ›ilor care respectÄƒ condiÈ›ia impusÄƒ de replica
% Detectivului B.
%
% AtenÈ›ie: informaÈ›ia ce trebuie filtratÄƒ acum este cea care
% corespunde primelor douÄƒ replici.

suspect3(Nume:Masina:Arma):-
    suspect2(Nume:Masina:Arma),
    suspect2(Nume1:_:Arma),
    Nume1 \= Nume.

% ----------------------------------------------------------------------------
% A patra replicÄƒ:
%
% Detectivul A: Eu tot nu È™tiu!
%
% 10. (2p) Scrue un predicat suspect4/1 care este adevÄƒrat doar pentru
% numele suspecÈ›ilor care respectÄƒ condiÈ›ia impusÄƒ de replica
% Detectivului A.
%
% AtenÈ›ie: informaÈ›ia ce trebuie filtratÄƒ acum este cea care
% corespunde primelor trei replici.

suspect4(Nume:Masina:Arma):-
    suspect3(Nume:Masina:Arma),
    suspect3(Nume1:Masina:_),
    Nume1 \= Nume.

% ----------------------------------------------------------------------------
% A cincea replicÄƒ:
%
% Detectivul B: Eu am aflat!
%
% 11. (2p) Scrue un predicat suspect5/1 care este adevÄƒrat doar pentru
% numele suspecÈ›ilor care respectÄƒ condiÈ›ia impusÄƒ de replica
% Detectivului B.
%
% AtenÈ›ie: informaÈ›ia ce trebuie filtratÄƒ acum este cea care
% corespunde primelor patru replici.

suspect5(Nume:Masina:Arma):-
    suspect4(Nume:Masina:Arma),
    \+ (suspect4(Nume1:_:Arma), Nume1 \= Nume).

% ----------------------------------------------------------------------------
% A È™asea replicÄƒ:
%
% Detectivul A: È˜i eu am aflat!
%
% 12. (2p) Scrie un predicat suspect6/1 care este adevÄƒrat doar pentru
% numele suspecÈ›ilor care respectÄƒ condiÈ›ia impusÄƒ de replica
% Detectivului A.
%
% AtenÈ›ie: informaÈ›ia ce trebuie filtratÄƒ acum este cea care
% corespunde primelor cinci replici.

suspect6(Nume:Masina:Arma):-
    suspect5(Nume:Masina:Arma),
    \+ (suspect5(Nume1:Masina:_), Nume1 \= Nume).

% ------------------------------------------------------------------------------
% ------------------------------------------------------------------------------

success_message(P, I):-
    format('[~2f] Bravo, exerciÈ›iul ~d este rezolvat corect!~n', [P,I]).

fail_message(I):-
    format('[0.00] ExerciÈ›iul ~w nu este rezolvat corect.~n', [I]).

test_1:-
    setof(Nume:Masina:Arma, suspect(Nume:Masina:Arma), All),
    maplist(==, All,
            [aurel:ford:sabie, bogdan:bmw:pistol,
             cosmin:bmw:arbaleta, daniel:ford:grenada, eugen:bmw:grenada,
             florin:dacia:sabie, george:fiat:pistol, horia:audi:arbaleta,
             irina:dacia:pusca, jean:fiat:cutit, kiki:audi:prastie,
             laura:seat:pusca, marian:mercedes:cutit, nicodim:opel:prastie,
             ovidiu:honda:maceta, paul:honda:mitraliera]),
    !,
    success_message(1.0, 1).

test_1:-
    fail_message(1).

test_2:-
    au_bmw(ListaNume), ListaNume == [bogdan, cosmin, eugen],
    !,
    success_message(0.5, 2).

test_2:-
    fail_message(2).

test_3:-
    au_marca(bmw, BMW), BMW == [bogdan, cosmin, eugen],
    au_marca(dacia, Dacia), Dacia == [florin, irina],
    au_marca(seat, Seat), Seat == [laura],
    !,
    success_message(0.5, 3).

test_3:-
    fail_message(3).

test_4:-
    arme_bmw(ListaArme), ListaArme == [arbaleta, grenada, pistol],
    !,
    success_message(0.5, 4).

test_4:-
    fail_message(4).

test_5:-
    arme_marca(bmw, BMW), BMW == [arbaleta, grenada, pistol],
    arme_marca(dacia, Dacia), Dacia == [pusca, sabie],
    arme_marca(seat, Seat), Seat == [pusca],
    !,
    success_message(0.5, 5).

test_5:-
    fail_message(5).

test_6:-
    marci_arma_unica(Marci),
    msort(Marci, Sorted),
    Sorted == [mercedes, opel, seat],
    !,
    success_message(1, 6).

test_6:-
    fail_message(6).

test_7:-
    setof(Nume:Masina:Arma, suspect1(Nume:Masina:Arma), Lista),
    Lista = [aurel:ford:sabie,bogdan:bmw:pistol,cosmin:bmw:arbaleta,
             daniel:ford:grenada,eugen:bmw:grenada,florin:dacia:sabie,
             george:fiat:pistol,horia:audi:arbaleta,irina:dacia:pusca,
             jean:fiat:cutit,kiki:audi:prastie,laura:seat:pusca,
             marian:mercedes:cutit,nicodim:opel:prastie],
    !,
    success_message(2, 7).

test_7:-
    fail_message(7).

test_8:-
    setof(Nume:Masina:Arma, suspect2(Nume:Masina:Arma), Lista),
    Lista == [aurel:ford:sabie,bogdan:bmw:pistol,cosmin:bmw:arbaleta,
              daniel:ford:grenada,eugen:bmw:grenada,florin:dacia:sabie,
              george:fiat:pistol,horia:audi:arbaleta,irina:dacia:pusca,
              jean:fiat:cutit,kiki:audi:prastie],
    !,
    success_message(2, 8).

test_8:-
    fail_message(8).

test_9:-
    setof(Nume:Masina:Arma, suspect3(Nume:Masina:Arma), Lista),
    Lista == [aurel:ford:sabie,bogdan:bmw:pistol,cosmin:bmw:arbaleta,
              daniel:ford:grenada,eugen:bmw:grenada,florin:dacia:sabie,
              george:fiat:pistol,horia:audi:arbaleta],
    !,
    success_message(2, 9).

test_9:-
    fail_message(9).

test_10:-
    setof(Nume:Masina:Arma, suspect4(Nume:Masina:Arma), Lista),
    Lista == [aurel:ford:sabie,bogdan:bmw:pistol,cosmin:bmw:arbaleta,
              daniel:ford:grenada,eugen:bmw:grenada],
    !,
    success_message(2, 10).

test_10:-
    fail_message(10).

test_11:-
    setof(Nume:Masina:Arma, suspect5(Nume:Masina:Arma), Lista),
    Lista = [aurel:ford:sabie,bogdan:bmw:pistol,cosmin:bmw:arbaleta],
    !,
    success_message(2, 11).

test_11:-
    fail_message(11).

test_12:-
    setof(Nume:Masina:Arma, suspect6(Nume:Masina:Arma), Lista),
    Lista = [aurel:ford:sabie],
    !,
    success_message(2, 12).

test_12:-
    fail_message(12).


% ------------------------------------------------------------------------------

:-
    nl,
    test_1,
    test_2,
    test_3,
    test_4,
    test_5,
    test_6,
    test_7,
    test_8,
    test_9,
    test_10,
    test_11,
    test_12.
%% ----------------------------------------
%% ----------------------------------------
%% Atenție la antetele predicatelor și la prefixul parametrilor
%% p(+Arg1, -Arg2, ?Arg3)
%%  * Arg1 va fi instanțiat atunci când se va încerca satisfacerea p/3
%%  * Arg2 se va instanția odată cu satisfacerea p/3
%%  * Arg3 va putea fi instanțiat sau nu atunci când se va satisface p/3:
%%
%% Interogați Prolog cu "checkXX." pentru a verifica rezolvarea exercițiului XX.
%% Pentru a vedea progresul general, trimiteți scopul "check_all".
%% ----------------------------------------
%% ----------------------------------------

%% 1. (1p)
%% my_concat/3
%% my_concat(?List1, ?List2, ?List)
%% 'List' reprezintă o listă formată prin concatenarea listelor 'List1'
%% și 'List2'.

my_concat([], List, List).
my_concat(List, [], List).
my_concat([Head | X], Y, [Head | Z]) :-
    my_concat(X, Y, Z).

check1:-
        my_concat([], [], La), La == [], write('.'),
        my_concat(L1b, [1,2], [1,2]), L1b == [], write('.'),
        my_concat([1,2,3], L2c, [1,2,3,4,5]), L2c == [4, 5], write('.'),
        my_concat([a, b, c], [d], [a, b, c, d]), write('.'),
        my_concat([X1, X2], [X1, X2], [1, 2, 1, 2]), write('.'),
        \+ my_concat([X1, X2], [X1, X2], [1, 2, 3, 4]), write('.'),
        writeln('Exercițiul 1 rezolvat corect!'),
        !.

%% ----------------------------------------

%% 2a. (1p)
%% my_reverse/2
%% my_reverse(?List, ?RevList)
%% 'RevList' este o listă ce conține elementele listei 'List' în ordine inversă.
%% Regulile pot conține și predicatul my_concat

my_reverse([], []).
my_reverse([Head | X], Y):-
    my_reverse(X, L),
    my_concat(L, [Head], Y).

check2a:-
        my_reverse([], []), write('.'),
        my_reverse([1,2,3], [3,2,1]), write('.'),
        my_reverse([1,2,3], Rev3), Rev3 == [3,2,1], write('.'),
        my_reverse(List4, [3,2,1]), List4 == [1,2,3], write('.'),
        my_reverse([1,X2,X3], [3,2,X1]), X1 == 1, X2 == 2, X3 == 3, write('.'),
        writeln('Exercițiul 2a rezolvat corect!'),
        !.

%% ----------------------------------------

%% 2b. (1p)
%% my_reverse_acc/3
%% my_reverse_acc(?List, ?Acc, ?RevList)
%% 'RevList' este o listă ce conține elementele listei 'List' în ordine inversă
%% și elementele listei 'Acc'.
%% (Indicație: 'Acc' se va comporta precum un acumulator)
%% Regulile nu trebuie să conține alte predicate (în afară de "cut" și ",").

my_reverse_acc([],List,List).
my_reverse_acc([Head | X], L, Y):- 
    A = [Head | L],
    my_reverse_acc(X, A, Y).

check2b:-
        my_reverse_acc([], [], []), write('.'),
        my_reverse_acc([1,2,3], [0], [3,2,1,0]), write('.'),
        my_reverse_acc([1,2,3], [0], Rev3), Rev3 == [3,2,1,0], write('.'),
        my_reverse_acc(List4, [0], [3,2,1,0]), List4 == [1,2,3], write('.'),
        my_reverse_acc([X2,1], [3], [X1,2,3]), X1 == 1, X2 == 2, write('.'),
        writeln('Exercițiul 2b rezolvat corect!'),
        !.

check2:-
        check2a, check2b.

%% ----------------------------------------

%% 3. (1.5p)
%% extract/4
%% extract(+List, +Start, +End, -Range)
%% 'Range' reprezintă lista formată din elementele listei 'List' aflate
%% pe pozițiile din intervalul 'Start' .. 'End'. 'Start' va fi întotdeauna
%% mai mic decât 'End'. Primul element se află pe poziția 0. Dacă 'End'
%% depășește lungimea listei, 'Range' va conține toate elementele de la 'Start'
%% la finalul listei.

extract(L, 0, _, L2).
extract([Head | X], 0, B, Y):- 
    B1 is B - 1,
    extract(X, 0, B1, Y).
extract([Head | X], A, B, Y):- 
    A1 is A - 1,
    B1 is B - 1,
    extract(X, A1, B1, Y).

check3:-
        extract([a,b,c,d,e], 0, 3, [a,b,c,d]), write('.'),
        extract([a,b,c,d,e], 1, 10, [b,c,d,e]), write('.'),
        extract([a,b,C,D,e], 2, 4, [c,d,e]), C == c, D == d, write('.'),
        extract([a,b,C1,D1,e], 2, 4, [C2,D2,e]), C1 == C2, D1 == D2, write('.'),
        extract([a,b,c,_,d], 3, 4, [X,X]), write('.'),
        writeln('Exercițiul 3 rezolvat corect!'),
        !.

%% ----------------------------------------

%% 4a. (1p)
%% factorial/2
%% factorial(+N, -Fact)
%% 'Fact' este factorialul lui 'N'.
%% N va fi mereu legat la un număr natural.

factorial(0, 1).
factorial(N, Fact):- 
    N > 0,
    Aux is N-1,
    factorial(Aux, Factaux),
    Fact is N * Factaux.

check4a:-
        factorial(1, F1), F1 == 1, write('.'),
        factorial(4, F2), F2 == 24, write('.'),
        factorial(5, 120), write('.'),
        factorial(6, 720), write('.'),
        factorial(7, 5040), write('.'),
        writeln('Exercițiul 4a rezolvat corect!'),
        !.

%% ----------------------------------------

%% 4b. (1p)
%% factorial2/2
%% factorial2(?N, ?Fact)
%% 'Fact' este factorialul lui 'N'.
%% Cel puțin unul dintre cele două argumente trebuie să fie legat la un număr.

factorial2(1, 1).
factorial2(N, Fact):- 
    factorial2(Aux, Factaux),
    N is Aux + 1,
    Fact is Factaux * N.

check4b:-
        factorial2(2, F1), F1 == 2, write('.'),
        factorial2(4, F2), F2 == 24, write('.'),
        factorial2(N3, 120), N3 == 5, write('.'),
        factorial2(N4, 720), N4 == 6, write('.'),
        factorial2(7, 5040), write('.'),
        writeln('Exercițiul 4b rezolvat corect!'),
        !.

check4:-
        check4a,
        check4b.

%% ----------------------------------------

%% 5. (1p)
%% palindrom/2
%% palindrom(+List)
%% 'List' este un palindrom.

palindrom(L):- 
    my_reverse(L,L).

check5 :-
        palindrom([1,2,3,2,1]), write('.'),
        palindrom([1,2,3,3,2,1]), write('.'),
        \+ palindrom([1,2,3,0,2,1]), write('.'),
        palindrom([1,2,3,X3,X2,X1]), X3 == 3, X2 == 2, X1 == 1, write('.'),
        \+ palindrom([1,2,3,X,_,X]), write('.'),
        writeln('Exercițiul 5 rezolvat corect!'),
        !.


%% ----------------------------------------

%% 6. (1.5p)
%% sublista/2
%% sublista(+List, ?SubList)
%% 'SubList' este o sublistă a lui 'List' ('SubList' poate fi obținută prin
%% eliminarea a zero sau mai multe elemente din 'List'

sublista( _ , [] ).
sublista( [X | Lista1], [X | Lista2]):- sublista(Lista1, Lista2).
sublista( [_ | Lista1], [X | Lista2]):- sublista(Lista1, [X | Lista2]).


check6 :-
        sublista([1,2,3,4,5],[2,3,4]), write('.'),
        sublista([1,2,3,4,5],[1,2,3,4,5]), write('.'),
        \+ sublista([1,2,3,4,5],[2,1,4]), write('.'),
        findall(S4, sublista([1,2,3], S4), All4),
        sort(All4, [[],[1],[1,2],[1,2,3],[1,3],[2],[2,3],[3]]), write('.'),
        sublista([X1,X2,X3],[Y1,Y2,Y3]), X1==Y1, X2==Y2, X3==Y3, write('.'),
        writeln('Exercițiul 6 rezolvat corect!'),
        !.


%% ----------------------------------------
%% ----------------------------------------
%% ----------------------------------------

%% Se dau urmatoarele fapte care descriu arborele genealogic al unei familii.
%% În această familie nu se practică divorțul, incestul sau adulterul
%% și nu există două persoane diferite cu același nume.

%% parinte/2
%% parinte(+Parinte, +Copil)
%% 'Copil' este copilul lui 'Parinte'.

parinte(ioana, radu).
parinte(ioana, miruna).
parinte(alin, radu).
parinte(alin, miruna).
parinte(ana, mihai).
parinte(ana, wendy).
parinte(radu, mihai).
parinte(radu, wendy).
parinte(mihai, dragos).
parinte(mihai, sorina).
parinte(mihai, ema).
parinte(elena, dragos).
parinte(elena, sorina).
parinte(elena, ema).

%% 7. (2p)
%% Scrieți urmatoarele reguli pentru a putea obține mai multe informații legate
%% de relațiile de rudenie.

%% stramos/2
%% stramos(?Stramos, ?Nepot)
%% 'Nepot' este un urmaș al lui 'Stramos'

stramos(Stramos, Nepot):- parinte(Stramos, Nepot).
stramos(Stramos, Nepot):-
    parinte(Stramos, Parinte),
    stramos(Parinte, Nepot).

%% soti/2
%% soti(+Sot1, ?Sot2)
%% 'Sot1' si 'Sot2' au cel puțin un copil impreună.

soti(Sot1, Sot2):- 
    parinte(Sot1, Fiu),
    parinte(Sot2, Fiu),
    Sot1 \= Sot2, !.

%% frate/2
%% frate(+Frate1, ?Frate2)
%% 'Frate1' și 'Frate2' au cel puțin un parinte comun.

frate(Frate1, Frate2):- 
    parinte(Parinte, Frate1), !,
    parinte(Parinte, Frate2),
    Frate2 \= Frate1.

check7:-
        stramos(ana,sorina), write('.'),
        findall(X, stramos(ana,X), L1),
        permutation([wendy,ema,mihai,sorina,dragos],L1),!, write('.'),
        findall(X, stramos(mihai,X), L2),
        permutation([ema,sorina,dragos], L2),!, write('.'),
        findall(X, stramos(X,mihai), L3),
        permutation([ana,radu,ioana,alin], L3),!, write('.'),
        soti(radu,ana), write('.'),
        \+ soti(dragos,ema), write('.'),
        findall(X, soti(mihai,X), L4),
        permutation([elena], L4), !, write('.'),
        frate(mihai,wendy), write('.'),
        \+ frate(mihai,ana), write('.'),
        findall(X, frate(sorina,X), L5),
        permutation([dragos,ema], L5), write('.'),
        writeln('Exercițiul 7 rezolvat corect!'),
        !.

%% ----------------------------------------

%% 8. (2p)
%% rude_alianta/2
%% rude_alianta(+Ruda1, ?Ruda2)
%% 'Ruda2' este o rudă prin alianță a lui 'Ruda1'

rude_alianta(_, _):- fail.

check8:-
        findall(X,rude_alianta(elena,X),L1),
        permutation([wendy,mihai,radu,ana,miruna,ioana,alin],L1), !, write('.'),
        findall(X,rude_alianta(ana,X),L2),
        permutation([miruna,ioana,alin,radu],L2),!, write('.'),
        findall(X,rude_alianta(radu,X),L3),
        permutation([ana],L3), !, write('.'),
        findall(X,rude_alianta(alin,X),L4),
        permutation([ioana],L4), write('.'),
        writeln('Exercițiul 8 rezolvat corect!'),
        !.

%% ----------------------------------------
%% ----------------------------------------

%% 9. (2p)
%% merge_sort/2
%% merge_sort(+List,-SortedList)
%% 'SortedList' conține elementele listei 'List' în ordine crescătoare
%% Satisfacerea predicatul merge_sort trebuie să realizeze sortarea listei
%% 'List' prin metoda merge_sort.
%% Se vor scrie 2 predicate auxiliare: split/3 și merge/3.

merge_sort(_, _):- fail.

check9:-
        merge_sort([], []), write('.'),
        merge_sort([1], [1]), write('.'),
        merge_sort([1,3,2], [1,2,3]), write('.'),
        merge_sort([7,4,1,3,4,2], [1,2,3,4,4,7]), write('.'),
        merge_sort([7,4,1,3,4,2], L4), L4 == [1,2,3,4,4,7], write('.'),
        writeln('Exercițiul BONUS rezolvat corect!'),
        !.

%% ----------------------------------------
%% ----------------------------------------


check_all:-
        retractall(punct(_, _)),
        once((check1, assert(punct(1, 1)) ; assert(punct(1, 0)))),
        once((check2a, assert(punct(21, 1)) ; assert(punct(21, 0)))),
        once((check2b, assert(punct(22, 1)) ; assert(punct(22, 0)))),
        once((check3, assert(punct(3, 1.5)) ; assert(punct(3, 0)))),
        once((check4a, assert(punct(41, 1)) ; assert(punct(41, 0)))),
        once((check4b, assert(punct(42, 1)) ; assert(punct(42, 0)))),
        once((check5, assert(punct(5, 1)) ; assert(punct(5, 0)))),
        once((check6, assert(punct(6, 1.5)) ; assert(punct(6, 0)))),
        once((check7, assert(punct(7, 2)) ; assert(punct(7, 0)))),
        once((check8, assert(punct(8, 2)) ; assert(punct(8, 0)))),
        once((check9, assert(punct(b, 2)) ; assert(punct(b, 0)))),
        fail.

check_all:-
        findall(P, punct(_, P), L),
        sum_list(L, S),
        format('Punctaj total: ~f~n',[S]).

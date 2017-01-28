%% -------------------------------------------------------------
%% -------------------------------------------------------------

%% -- BACKTRACKING ATUNCI CÂND CUNOAȘTEM LUNGIMEA SOLUȚIEI --

%%% 1. (4p)
%% Înțelegeți predicatele solve_queens/1, template/1 și correct/1.
%% Observați că lipsește definiția predicatelui safe/2.

%% template/1
%% template(?List)
%% List are forma unei soluții pentru problema celor opt regine.
%% Lungimea soluției este cunoscută și fixă.
template([1/_, 2/_, 3/_, 4/_, 5/_, 6/_, 7/_, 8/_]).

%% correct/1
%% correct(?Solution)
%% Solution reprezintă o soluție validă pentru problema celor opt regine.
correct([]):-!.
correct([X/Y|Others]):-
        correct(Others),
        member(Y, [1, 2, 3, 4, 5, 6, 7, 8]),
        safe(X/Y, Others).

%% solve_queens/1
%% solve_queens(-Solution)
%% Solution este o soluție a problemei celor opt regine.
solve_queens(S):-template(S), correct(S).

%% Scrieți predicatul safe/2 utilizat în rezolvarea problemei celor opt regine.
%% Predicatul va avea antetul safe(+X/Y, +Others) cu semnificația că se verifică
%% dacă plasarea reginei de coloana X pe linia Y nu se atacă cu o altă regină
%% din lista Others. Aceasta are forma [X1/Y1, X2/ Y2/ ...].

%% safe/2
%% safe(+X/Y, +Others)

safe(X/Y, []).
safe(X/Y, [A/B | Others]):-
    \+ (Y == B),
    \+ (X == A),
    (abs(X - A) =\= abs(Y - B)),
    safe(X/Y, Others).

check1:-
        \+ safe(7/1, [8/1]), write('.'),
        \+ safe(7/1, [8/2]), write('.'),
        safe(7/1, [8/3]), write('.'),
        \+ safe(7/5, [8/4]), write('.'),
        safe(7/3, [8/5]), write('.'),
        safe(4/1, [5/3, 6/5, 7/2, 8/4]), write('.'),
        \+ safe(4/1, [5/4, 6/2, 7/7, 8/5]), write('.'),
        safe(1/4, [2/6, 3/8, 4/2, 5/7, 6/1, 7/3, 8/5]), write('.'),
        findall(Sol, solve_queens(Sol), All), length(All, 92), write('.'),
        writeln('Exercițiul 1 rezolvat corect!'),
        !.

%% Întrebați-l pe Prolog "solve_queens(Sol)" pentru a vizualiza soluțiile.

%% -------------------------------------------------------------
%% -------------------------------------------------------------

%% -- BACKTRACKING ATUNCI CÂND SOLUȚIA POATE AVEA LUNGIME VARIABILĂ --

%%% 2. (6p)
%% Înțelegeți cum funcționeză predicatele solve și search pentru rezolvarea
%% unei probeleme de căutare în spațiul stărilor. Observați utilizarea
%% predicatelor initial_state/1, final_state/1 și next_state/2.

search([CurrentState | Other], Solution):-
        final_state(CurrentState),
        !,
        reverse([CurrentState | Other], Solution).

search([CurrentState|Other], Solution):-
        next_state(CurrentState, NextState),
        \+ member(NextState, Other),
        search([NextState,CurrentState|Other], Solution).

solve(Solution):-
        initial_state(State),
        search([State], Solution).

opus(est, vest).
opus(vest, est).

%% Rescrieți predicatele initial_state/1, final_state/1, și next_state/2 pentru
%% a rezolva problema misionarilor și a canibalilor.

%% Problema Misionarilor și a Canibalilor
%% Fie un râu, fie trei misionari, fie trei canibali și fie și o barcă. Râul
%% are două maluri. Misionarii, canibalii și barca se află pe unul dintre
%% maluri și vor să ajungă pe celălalt. Găsiți o secvență de traversări ale
%% râului de pe o parte pe cealaltă astfel încât: niciodată să nu rămână pe un
%% mal mai mulți canibali decât misionari, barca să traverseze râul cu cel puțin
%% o persoană și maxim două, indiferent de preferințele culinare.

%% Atenție, nu lăsați în spațiul de lucru predicatele pentru ambele probleme!

genereaza(state(0, 0, est), _, []).
genereaza(CurrentState, Visited, [Move | RestOfMoves]) :-
        next_state(CurrentState, NextState),
        \+ (member(NextState, Visited)),
        executa(CurrentState, NextState, Move),
        genereaza(NextState, [NextState | Visited], RestOfMoves).


executa(state(M1,C1,vest), state(M2,C2,est), miscare(M,C,est)) :-
    M is M2,
    C is C2.

executa(state(M1,C1,est), state(M2,C2,vest), miscare(M,C,vest)) :-
    M is M2,
    C is C2.

initial_state(3,3,vest).

final_state(0,0,est).


%% muta(X,Y)
muta(2,0).
muta(1,0).
muta(1,1).
muta(0,1).
muta(0,2).

%% save(X,Y)
save(X,X).
save(3,X).
save(0,X).


%% De La Vest la est.

next_state(state(NM1,NC1,vest),state(NM2,NC2,est)) :-
    muta(NM,NC),
    NM =< NM1,
    NC =< NC1,
    NM2 is NM1 - NM,
    NC2 is NC1 - NC,
    save(NM2,NC2).


%% De la Est la vestt.

next_state(state(NM1,NC1,est),state(NM2,NC2,vest)) :-
    muta(NM,NC),
    NM2 is NM1 + NM,
    NC2 is NC1 + NC,
    NM2 =< 3,
    NC2 =< 3,
    save(NM2,NC2).

check2:-
        findall(_, solve(_), AllSol), length(AllSol, 4), write('.'),
        writeln('Exercițiul 2 rezolvat corect!'),
        !.

%% -------------------------------------------------------------
%% -------------------------------------------------------------

%%% 3 (BONUS). (3p)
%% Implementați un predicat bfs/3 care să descrie un mecanism de căutare în
%% lățime într-un graf. Se dau predicatele initial_node/1, final_node/1 și
%% edge/2. Observați similaritatea cu initial_state/1, final_state/1 și
%% next_state/2.

do_bfs(Solution):-
        initial_node(StartNode),
        bfs([(StartNode,nil)], [], Discovered),
        extract_path(Discovered, Solution).

%% bfs/3
%% bfs(+Frontier, +Closed, -Solution)
%% Frontier reprezintă coada nodurilor ce vor fi explorate, Closed reprezintă
%% lista nodurilor vizitate deja, iar Solution va reprezenta lista finală a
%% nodurilor vizitate până la găsirea soluției.
%% Toate cele 3 liste vor avea elementele în forma pereche (Nod, Părinte).

bfs(_, _, _):-!, fail.


%% extract_path/3
%% extract_path(Discovered, Solution)
%% Solution reprezintă calea de la nodul inițial la cel final extrasă din
%% lista nodurilor vizitate (dată sub formă de perechi (Nod, Părinte).

extract_path(_, _):-fail.


%%% Testare

edge(a,b).
edge(a,c).
edge(a,d).
edge(c,e).
edge(c,f).
edge(d,h).
edge(e,a).
edge(e,g).
edge(f,a).
edge(f,g).
edge(g,h).

initial_node(a).
final_node(h).

check3:-
        do_bfs(Sol), Sol == [a,d,h],
        writeln('.Exercițiul 3 rezolvat corect!'),
        !.


%% -------------------------------------------------------------
%% -------------------------------------------------------------

%%% 4. BONUS. (2p)
%% Scrieți un predicat dfs/3 care să descrie un mecanism de căutare în adâncime
%% într-un graf. La fel ca la exercițiul 3, se dau predicatele initial_node/1,
%% final_node/1, și edge/2.

do_dfs(Solution):-
        initial_node(StartNode),
        dfs([(StartNode, nil)], [], Discovered),
        extract_path(Discovered, Solution).


%% dfs/3
%% dfs(+Frontier, +Closed, -Solution)
%% Frontier este stiva de noduri de explorat,  Closed reprezintă lista nodurilor
%% vizitate deja sub fomar unor perechi (Nod, Părinte), iar Solution reprezintă
%% lista tuturor nodurilor explorate în parcurgerea în adâncime.

dfs(_, _, _):-!, fail.


%%% Testare

check_bonus:-
        do_dfs(Path), Path == [a,c,e,g,h],
        writeln('.Exercițiul BONUS rezolvat corect!'),
        !.

%% -------------------------------------------------------------
%% -------------------------------------------------------------

check_all:-
        retractall(punct(_, _)),
        once((check1, assert(punct(1, 2)) ; assert(punct(1, 0)))),
        once((check2, assert(punct(2, 4)) ; assert(punct(2, 0)))),
        once((check3, assert(punct(3, 4)) ; assert(punct(3, 0)))),
        once((check_bonus, assert(punct(b, 2)) ; assert(punct(b, 0)))),
        fail.

check_all:-
        findall(P, punct(_, P), L),
        sum_list(L, S),
        format('Punctaj total: ~f~n',[S]).

%:-check_all.

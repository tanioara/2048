Tema 2 - 2048

Cerinta 1
Am realizat meniul interactiv cu cele 3 optiuni,
am centrat textul si am folosit functiile necesare
pentru a atribui culori si a evidentia mereu optiunea
curenta. 
In main, am implementat logica pt alegera optiunii,
la apasarea tastelor sus sau jos, numarul asociat alegerii
creste sau scade, iar in momentul apasarii tastei enter
se tine cont de alegere si se executa actiunile aferente.

Cerinta 2
Am creat grid-ul pentru joc, alcatuit din 16 window-uri
dispuse sub forma unei matrici de 4x4 ce isi ajusteaza, 
la afisarea pe ecran, dimensiunile in functie de dimensiunea
terminalului.
In partea dreapta afisez data si ora curente, urmate de scor
si de o legenda a comenzilor valide, si anume mutarile prin 
sageti, dar si functiile de quit si undo.
Am folosit functia populate_grid pentru a adauga cate o 
valoare aleatorie noua pe tabla de joc, de "nr" ori.

Cerinta 3
Am facut 4 functii, cate una pentru fiecare directie in care
mutarile erau posibile.
In functia start, m-am asigurat ca mutarea a fost intr-adevar
valida, adica a adus o schimbare tablei de joc, pentru a sti
cand e nevoie sa adaug o noua celula. 
Fiecare functie "move_" muta celulele in directia potrivita
si efectueaza doar o prima imbinare intre doua celule.
La fiecare operatie, scorul este incrementat si afisat in partea
dreapta a ecranului.
Am ales culori pentru fiecare valoare numerica, dar si pentru
background-ul intregului joc si pentru text, incarcand sa fac
interfata mea grafica sa fie cat mai asemanatoare cu cea a jocului
original. 

Cerinta 4
Am implementat miscarea automata a celulelor dupa ce
jucatorul nu a mai apasat nicio tasta timp de 10 secunde.
Am folosit o functie best_direction care determina
cea mai eficienta mutare comparand numarul celulelor goale 
in cazul fiecarei dintre cele 4 directii.
In main, odata cu fiecare tasta apasata am actualizat
valoare variabilei care calculeaza cat timp a trecut
de la ultima mutare.

Cerinta 5
Am implementat functiile pentru game over si win.
In momentul in care se gaseste pe tabla o celula cu
valoarea 2048 sau in care tabla e plina si nu mai
exista mutari posibile, jocul afiseaza un mesaj in 
parte dreapta a ecranului si continua sa afiseze
tabla de joc pentru inca 10 secunde, dupa care se
revine la meniul principal.

Ca functionalitati extra, am adaugat functia de UNDO,
pentru implementarea careia m-am folosit de o copie
a tablei de joc.
Am folosit cate o culoare diferita pentru fiecare numar, 
culori pe care le-am initializat cu ajutorul unei functii
auxiliare initialize_colors.
createTree - aloca memorie pentru un nou arbore, initializeaza functiile din structura unui arbore cu functiile primite ca parametru de functiile,
            initializeaza size-ul arborelui cu 0 si root-ul cu NULL si returneaza arborele creat;

isEmty - verifica daca root-ul arborelui este NULL, daca da returneaza 1, daca nu returneaza 0;

search -  daca nodul x este NULL sau elementul nodului x este egal cu elem primit ca parametru, vom returna x
            daca elementul nodului x este mai mic decat elem primit ca parametru, vom apela recursiv functia pentru urmatorul nod din dreapta
            daca elementul nodului x este mai mare decat elem primit ca parametru, vom apela recursiv functia pentru urmatorul nod la stanga;

minimim - daca nodul x primit ca parametru exista, ne ducem la cel mai din stanga nod si il returnam, acesta fiind minumul; daca nodul x nu exista returnam NULL;

maximum - daca nodul x primit ca parametru exista, ne ducem la cel mai din dreapta nod si il returnam, acesta fiind maximul; daca nodul x nu exista returnam NULL;

successor - creaza un nou nod care va deveni root ul arborelui. 
            daca nodul primit ca parametru este null sau acesta este deja maximul din arbore, inseamna ca nodul nu are succesor inordine si va returna NULL
            daca mai exista nod in dreapta lui x, vom returna minimul pentru acel nod pentru a gasi successorul lui x
            altfel, atata timp cat x nu este in partea din stanga a parintelui sau, x va deveni parintele sau pana cand x devine un nod din dreapta, urmand sa 
            returnam parintele acelui nod pentru a gasi successorul nodului initial x.

predecessor - este functia exact inversa lui successor.

updateHeight -  pentru un nod primit ca parametru va calcula inaltimea din stanga si pe cea din dreapta si va actualiza inaltimea nodului ca fiind maximul dintre
                acestea 2, +1.

avlRotateLeft - vom crea un nod nou y care va fi in dreapta nodului x primit ca parametru; ne propunem sa facem o rotatie la stanga pentru ca ulterior sa ne ajute
                sa reechilibram arborele. nodul din stanga lui y se va muta in dreapta lui x, deci x va fi parintele acestuia, in cazul in care nodul exista;
                mai departe ne dorim sa facem schimbarea intre x si y. prima data verificam in ce parte este x fata de parintele sau si legam y de parintele lui x
                in aceeasi parte; in cazul in care x era root, y devine root. dupa, vom face ca x s afie in stanga lui y, iar y sa fie parintele lui x pentru a termina 
                rotatia; evident, la final vom reactualiza inaltimile pentru ambele noduri x si y folosindu-ne de functia updateHeight.

avlRotateRight - functia exact inversa avlRotateLeft
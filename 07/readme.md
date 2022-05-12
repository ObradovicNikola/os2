# Neefikasni faktorijel

Napraviti program koji racuna faktorijel datog broja tako sto pravi po jedan proces za racunanje svakog koraka. Svaki proces (osim poslednjeg) treba od deteta da dobije rezultat i da ga pomnozi sa adekvatnim brojem. Svi procesi (osim pocetnog) treba da rezultat vrate roditelju.

Za komunikaciju medju procesima koristiti pajpove.

Zapazanja kada se dete proces zavrsi sa greskom.
zadatak: racunamo faktorijel od 5, imamo lanac od 5 procesa
dete pise medjurezultat roditelju preko pajpa

Slucaj kada treci element u lancu izadje sa greskom
1) izlaz bez zatvaranja otvorenih krajeva pajpova
    posmatramo sta se desava u roditelju treceg elementa:
      - funkcija read vraca 0,
      u normalnim okolnostima, funkcija read bi vratila broj ucitanih bajtova
      - vrednost promenljive u koju se ucitava vrednost se ne menja
2) izlaz sa prethodno zatvorenim krajevima pajpova
    - desava se potpuno isti scenario kao pod 1)
    - ni u kom slucaju se ne desava zamrzavanje programa
    zato sto ako pogledamo posix dokumentaciju mozemo videti sta se desava sa otvorenim fajl deskriptorima ako se proces zavrsi:
    https://pubs.opengroup.org/onlinepubs/9699919799/functions/_Exit.html

    - All of the file descriptors, directory streams, conversion descriptors, and message catalog descriptors open in the calling process shall be closed.

    Ipak je operativni sistem dovoljno pametan da spreci beskonacno izvrsavanje programa.

Nakon ovog testa, pisemo kod da hendluje exit status deteta u roditelju...

primer hendlovanja jednog deteta: https://github.com/ObradovicNikola/os2/blob/master/07/errorKodDeteProcesa.c
primer hendlovanja greske u lancu: https://github.com/ObradovicNikola/os2/blob/master/07/errorULancuDeceProcesa.c


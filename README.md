# ORSI_Assignment02
A bemeneti fájlok egyike, az input_matrices.txt első sorában egy M pozitív egész olvasható, ennyi lineáris transzformációt kell elvégezni az objektumokat reprezentáló vektorokon, míg a következő 4xM sorban egy-egy 4x4es mátrix sorfolytonos reprezentációja található szóközökkel elválasztva. (4 egymás utáni sor jelent egy mátrixot.)

A másik fájl, az input_points.txt tartalmazza a pontok listáját, amikre alkalmazni kell az előbbi mátrixokkal való szorzást. Ennek első sora egy egész szám, N, ez után található N sor egy-egy 3 dimenziós vektor koordinátáit írja le (szintén szóközzel tagolva).

Input file

Egy lehetséges input_matrices.txt fájl: (Az alábbi mátrix-transzformációk pl. a 2x-es méretezés, 90°-os forgatást az X tengely körül, majd a (3;-2;4) vektorral való eltolást jelentik.)

    3
    2 0 0 0
    0 2 0 0
    0 0 2 0
    0 0 0 1
    1 0 0 0
    0 0 -1 0
    0 1 0 0
    0 0 0 1
    1 0 0 3
    0 1 0 -2
    0 0 1 4
    0 0 0 1
Egy lehetséges input_points.txt fájl:

    8
    1 1 1
    1 1 -1
    1 -1 1
    1 -1 -1
    -1 1 1
    -1 1 -1
    -1 -1 1
    -1 -1 -1
A számítást a későbbiekben megkönnyíti, ha a bemenet során a 3D-s vektorokat 4 dimenzióban reprezentáljátok, a negyedik koordinátát 1-re inicializálva. A mátrixszal való szorzás így lényegesen könnyebbé válik.

A feladatban az adatcsatorna tételére visszavezetve kell megoldani a kitűzött problémát!

A főfolyamat dolga, hogy beolvassa a mátrixokat, majd M threadet létrehozva, s azokat egy-egy transzformációnak megfeleletetve átadja nekik az megfelelő mátrixokat. A pontokat az első mátrixot reprezentáló szálnak kell elküldenie, majd az utolsó leképezést megvalósító gyerektől fogadnia a megfelelően transzformált vektorokat. Ezek után írja soronként az output.txt fájlba az így kapott eredményt.

Az indított szálak feladata, hogy fogadják a vektorokat a megelőző gyerektől (az első transzformáció esetén a main-től), elvégezzék a mátrix-vektor szorzást, majd továbbítsák az így kapott részeredményt a következő folyamatnak. (Az utolsó számítás esetén a mainnek / kiíró szálnak.)

A main létrehozhat egy különszálat, ami csak a kiírásért felel (az utolsó csatornaelemből olvas), ez nem minősül hibának.
Implementációs követelmények

A feladatot C++ nyelvben implementálva, a C++11 által biztosított <thread> segítségével kell megvalósítani.

https://people.inf.elte.hu/mykeesg/19_20_2/pipe.hpp itt található egy segédfájl.

A pipe.hpp fájlnak tartalmán nem kell (nem is szükséges) változtatni - ezt az osztály egy konkurens felhasználásra tervezett, szálbiztos implementációt tartalmaz egy olyan (generikus) adatszerkezetre, melynek van egy T pop() és egy push(T&) metódusa adatok továbbításához (ha üres adatszerkezetre hív pop()-ot a program, akkor nem elszáll segfaulttal / exceptionnel, hanem addig vár, amíg nem érkezik adat. Pont emiatt vigyázni kell, hogy ne okozzon deadlockot a hibásan megírt felhasználása).

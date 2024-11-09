#include <iostream>
#include <opencv2/core.hpp>    // osztalyok, strukturak, alapveto funkciok
#include <opencv2/highgui.hpp> // felulet
#include <opencv2/imgproc.hpp> // kepfeld. konyvtar, gyakran kell majd

using namespace std;
using namespace cv;

/// <summary>
/// Zold szin masolo
/// </summary>
/// <param name="rgb">eloterkep</param>
/// <param name="dest">hatter</param>
void Masol(const cv::Mat rgb, cv::Mat& dest) {
    // beallitjuk a fekete hatterunket azaz a dest -t, meretet es tipusat
    dest.create(rgb.size(), CV_8UC3);
    // az intenzitasat 0-ra allitjuk, igy lesz fekete
    dest.setTo(0);

    // a csatornakhoz kell, igy majd tudunk ra hivatkozni pl: c[1] - zold
    cv::Vec3b c;

    // bejarjuk a kepet

    for (int i = 0; i < rgb.rows; ++i) {
        for (int j = 0; j < rgb.cols; ++j) {
            c = rgb.at<cv::Vec3b>(i, j); // c -nek atadjuk a pontokat
            if (c[1] > c[0] && c[1] > c[2]) // itt azt vizsgaljuk, hogy a zold szin erosebb legyen, mint a többi
                dest.at<cv::Vec3b>(i, j) = c; // es amelyekre ez igaz azt a dest (fekete hatteru kép) -re masoljuk 
        }
    }
}

int main() {
    // beolvassuk a kepet
    Mat orig = imread("zold_alma.jpg", IMREAD_COLOR);
    // az otodere csokkentjuk
    resize(orig, orig, Size(orig.cols / 5, orig.rows / 5));

    // ellenorizzuk, hogy meg van-e a kep
    if (orig.empty())
    {
        cout << "A kep nem talalhato" << endl;
        exit(-1);
    }

    Mat dest_rgb;
    // alkalmazzuk a fugvenyunket
    Masol(orig, dest_rgb);

    // megjelenítjuk a kepernyon
    imshow("eredeti", orig);
    imshow("masolt", dest_rgb);

    waitKey(0);

    return 0;
}
/*
//______________________________________________________
//2.feladat:


#include <iostream>
#include <opencv2/core.hpp>    // osztalyok, strukturak, alapveto funkciok
#include <opencv2/highgui.hpp> // felulet
#include <opencv2/imgproc.hpp> // kepfeld. konyvtar, gyakran kell majd

using namespace std;
using namespace cv;

/// <summary>
/// Sziv forma eltuntetes
/// </summary>
/// <param name="rgb">eloterkep</param>
/// <param name="dest">hatter</param>
void vilagosMasol(const cv::Mat rgb, cv::Mat& dest) {
    // beallitjuk a fekete hatterunket azaz a dest -t, meretet es tipusat
    dest.create(rgb.size(), CV_8UC3);
    // az intenzitasat 0-ra allitjuk, igy lesz fekete
    dest.setTo(0);

    // a csatornakhoz kell, igy majd tudunk ra hivatkozni pl: c[1] - zold
    cv::Vec3b c;

    // bejarjuk a kepet
    for (int i = 0; i < rgb.rows; ++i) {
        for (int j = 0; j < rgb.cols; ++j) {
            c = rgb.at<cv::Vec3b>(i, j); // atadjuk a pontokat i , j 
            // megnezzuk, hogy mi a szin kodja az almaban talalhato szivnek, igy megkapjuk a harom szin skalankat
            // megnezzuk, hogy a kapott ertekkel a kivant eredmenyt kapjuk-e
            // ennek megfeleloen noveljuk/csokentjuk az erteket
            if (c[0] < 180 && c[1] < 195 && c[2] < 255)
                dest.at<cv::Vec3b>(i, j) = c; // elhelyezzuk a pontokat a kepen
        }
    }
}

int main() {
    // beolvassuk a kepet
    Mat orig = imread("piros_alma_sziv.jpg", IMREAD_COLOR);
    // ellenorizzuk, hogy meg van-e a kep
    if (orig.empty())
    {
        cout << "A kep nem talalhato" << endl;
        exit(-1);
    }

    Mat dest_rgb;
    // alkalmazzuk a fugvenyunket
    vilagosMasol(orig, dest_rgb);
    // megjelenítjuk a kepernyon
    imshow("eredeti", orig);
    imshow("masolt", dest_rgb);

    waitKey(0);

    return 0;
}
//______________________________________________________
//3.feladat:

#include <iostream>
#include <opencv2/core.hpp>    // osztalyok, strukturak, alapveto funkciok
#include <opencv2/highgui.hpp> // felulet
#include <opencv2/imgproc.hpp> // kepfeld. konyvtar, gyakran kell majd

using namespace std;
using namespace cv;

/// <summary>
/// Eloter masolo
/// </summary>
/// <param name="fg">eloterkep</param>
/// <param name="bg">hatter</param>
void dekoracioMasolas(const Mat fg, Mat& bg) {
    // a csatornakhoz kell, igy majd tudunk ra hivatkozni pl: c[1] - zold
    Vec3b c;

    // bejarjuk a kepet
    for (int i = 0; i < fg.rows; ++i) {
        for (int j = 0; j < fg.cols; ++j) {
            // atadjuk a pontokat i , j 
            c = fg.at<Vec3b>(i, j);

            // megvizsgaljuk a sorok es oszlopokat
            if (i < bg.rows and j < bg.cols) {
                // tetszoleges eltolassal felmasoljuk a pontokat
                bg.at<Vec3b>(i + 50, j + 300) = c;
                bg.at<Vec3b>(i + 450, j + 300) = c;
            }
        }
    }
}

int main() {
    // beolvassuk a kepeket
    Mat fg = imread("dekoracio.jpg");
    Mat bg = imread("hatter_halloween.jpeg");

    // ellenorizzuk, hogy meg vannak-e a kepek
    if (fg.empty() || bg.empty())
    {
        cout << "A kep nem talalhato" << endl;
        exit(-1);
    }
    // alkalmazzuk a fugvenyunket
    dekoracioMasolas(fg, bg);

    // megjelenítjuk a kepernyon
    imshow("dekoracio", fg);
    imshow("hatterrel", bg);
    waitKey(0);

    return 0;
}

//______________________________________________________
//4.feladat:

#include <iostream>
#include <opencv2/core.hpp>    // osztalyok, strukturak, alapveto funkciok
#include <opencv2/highgui.hpp> // felulet
#include <opencv2/imgproc.hpp> // kepfeld. konyvtar, gyakran kell majd

using namespace std;
using namespace cv;

/// <summary>
/// Zold szin masolo
/// </summary>
/// <param name="rgb">eloterkep</param>
/// <param name="dest">hatter</param>
void Masol(const cv::Mat rgb, cv::Mat& dest) {
    // beallitjuk a fekete hatterunket azaz a dest -t, meretet es tipusat
    dest.create(rgb.size(), CV_8UC3);
    // az intenzitasat 0-ra allitjuk, igy lesz fekete
    dest.setTo(0);

    // a csatornakhoz kell, igy majd tudunk ra hivatkozni pl: c[1] - zold
    cv::Vec3b c;

    // bejarjuk a kepet
    for (int i = 0; i < rgb.rows; ++i) {
        for (int j = 0; j < rgb.cols; ++j) {
            // c -nek atadjuk a pontokat
            c = rgb.at<cv::Vec3b>(i, j);
            // itt azt vizsgaljuk, hogy a zold szin erosebb legyen, mint a többi
            if (c[2] > c[1] && c[2] > c[0])
                // es amelyekre ez igaz azt a dest (fekete hatteru kép) -re masoljuk 
                dest.at<cv::Vec3b>(i, j) = c;
        }
    }
}

int main() {
    // beolvassuk a kepet
    Mat orig = imread("m&m.jpg", IMREAD_COLOR);

    // ellenorizzuk, hogy meg van-e a kep
    if (orig.empty())
    {
        cout << "A kep nem talalhato" << endl;
        exit(-1);
    }

    Mat dest_rgb;
    // alkalmazzuk a fugvenyunket
    Masol(orig, dest_rgb);

    // megjelenítjuk a kepernyon
    imshow("eredeti", orig);
    imshow("masolt", dest_rgb);

    waitKey(0);

    return 0;
}

//______________________________________________________
//HSV 
//1.FELADAT:

#include <iostream>
#include <opencv2/core.hpp>    // osztalyok, strukturak, alapveto funkciok
#include <opencv2/highgui.hpp> // felulet
#include <opencv2/imgproc.hpp> // kepfeld. konyvtar, gyakran kell majd

using namespace std;
using namespace cv;

int main() {
    // beolvassuk a kepet
    Mat cukorka = imread("m&m.jpg", IMREAD_COLOR);
    // ellenorizzuk, hogy van-e kep
    if (cukorka.empty())
    {
        cout << "A kep nem talalhato" << endl;
        exit(-1);
    }
    // seged valtozo a konvertalashoz
    Mat hsv;
    cvtColor(cukorka, hsv, COLOR_BGR2HSV);
    Mat dest = Mat::zeros(cukorka.size(), CV_8UC3);

    // bejarjuk a kepet
    for (int i = 0; i < cukorka.rows; ++i) {
        for (int j = 0; j < cukorka.cols; ++j) {
            // a matrix tipus "beegetese" miatt egyszerusodik a pontok elerese
            int hue = hsv.at<Vec3b>(i, j)[0];

            //a szurke pontok kizarasa miatt kell
            int saturation = hsv.at<Vec3b>(i, j)[1];
            // skala szerint be allitjuk a hue-t es meg nezzuk 
            // milyen szaturacioval kapnank a kivant kept
            if ((hue < 120 && hue > 100))

                // masolojuk a kepet
                dest.at<Vec3b>(i, j) = cukorka.at<Vec3b>(i, j);;
        }
    }
    //megjelenitjuk a kepeket
    imshow("eredeti", cukorka);
    imshow("kek_m&m", dest);
    waitKey();

    return 0;
}
//_______________________________________________________
//2.FELADAT:

#include <iostream>
#include <opencv2/core.hpp>    // osztalyok, strukturak, alapveto funkciok
#include <opencv2/highgui.hpp> // felulet
#include <opencv2/imgproc.hpp> // kepfeld. konyvtar, gyakran kell majd

using namespace std;
using namespace cv;

int main() {
    // beolvassuk a kepet
    Mat cukorka = imread("m&m.jpg", IMREAD_COLOR);

    // ellenorizzuk, hogy van-e kep
    if (cukorka.empty())
    {
        cout << "A kep nem talalhato" << endl;
        exit(-1);
    }

    // seged valtozo a konvertalashoz
    Mat hsv;
    cvtColor(cukorka, hsv, COLOR_BGR2HSV);
    // fekete kep letrehozasa
    Mat dest = Mat::zeros(cukorka.size(), CV_8UC3);

    // bejarjuk a kepet
    for (int i = 0; i < cukorka.rows; ++i) {
        for (int j = 0; j < cukorka.cols; ++j) {
            // a matrix tipus "beegetese" miatt egyszerusodik a pontok elerese
            int hue = hsv.at<Vec3b>(i, j)[0];

            //a szurke pontok kizarasa miatt kell
            int saturation = hsv.at<Vec3b>(i, j)[2];
            // skala szerint be allitjuk a hue-t es meg nezzuk 
            // milyen szaturacioval kapnank a kivant kept
            if ((hue < 120 && hue > 100) && saturation > 120)
                // a kep pontokat zold csatronara allitjuk
                dest.at<Vec3b>(i, j)[1] = 120;
        }
    }
    //megjelenitjuk a kepeket
    imshow("eredeti", cukorka);
    imshow("kek_m&m", dest);
    waitKey();

    return 0;
}

//_____________________________________________________________________
//3.FELADAT:

#include <iostream>
#include <opencv2/core.hpp>    // osztalyok, strukturak, alapveto funkciok
#include <opencv2/highgui.hpp> // felulet
#include <opencv2/imgproc.hpp> // kepfeld. konyvtar, gyakran kell majd

using namespace std;
using namespace cv;

int main() {
    // beolvassuk a kepet
    Mat img = imread("dekoracio.jpg", IMREAD_COLOR);

    // ellenorizzuk, hogy van-e kep
    if (img.empty())
    {
        cout << "A kep nem talalhato" << endl;
        exit(-1);
    }

    // seged valtozo a konvertalashoz
    Mat hsv;
    cvtColor(img, hsv, COLOR_BGR2HSV);
    // fekete kep letrehozasa
    Mat dest = Mat::zeros(img.size(), CV_8UC3);

    // bejarjuk a kepet
    for (int i = 0; i < img.rows; ++i) {
        for (int j = 0; j < img.cols; ++j) {
            // a matrix tipus "beegetese" miatt egyszerusodik a pontok elerese
            int hue = hsv.at<Vec3b>(i, j)[0];

            //a szurke pontok kizarasa miatt kell
            int saturation = hsv.at<Vec3b>(i, j)[1];
            // skala szerint be allitjuk a hue-t es meg nezzuk 
            // milyen szaturacioval kapnank a kivant kept
            if ((hue < 25 && hue > 0) && saturation > 60)
                // masoljuk a kepet a fekete hattere
                dest.at<Vec3b>(i, j) = img.at<Vec3b>(i, j);
        }
    }
    //megjelenitjuk a kepeket
    imshow("eredeti", img);
    imshow("kek_m&m", dest);
    waitKey();

    return 0;
}


//____________________________________________________________

//4.FELADAT:

#include <iostream>
#include <opencv2/core.hpp>    // osztalyok, strukturak, alapveto funkciok
#include <opencv2/highgui.hpp> // felulet
#include <opencv2/imgproc.hpp> // kepfeld. konyvtar, gyakran kell majd

using namespace std;
using namespace cv;

int main() {
    // beolvassuk a kepet
    Mat orig = imread("szolo.jpg", IMREAD_COLOR);
    resize(orig, orig, Size(orig.cols / 5, orig.rows / 5));

    // ellenorizzuk, hogy van-e kep
    if (orig.empty())
    {
        cout << "A kep nem talalhato" << endl;
        exit(-1);
    }

    // seged valtozo a konvertalashoz
    Mat hsv;
    cvtColor(orig, hsv, COLOR_BGR2HSV);
    // fekete kep letrehozasa
    Mat dest = Mat::zeros(orig.size(), CV_8UC3);
    Mat dest2 = Mat::zeros(orig.size(), CV_8UC3);

    for (int i = 0; i < orig.rows; ++i) {
        for (int j = 0; j < orig.cols; ++j) {
            // a matrix tipus "beegetese" miatt egyszerusodik a pontok elerese
            int hue = hsv.at<Vec3b>(i, j)[0];
            //a szurke pontok kizarasa miatt kell
            int saturation = hsv.at<Vec3b>(i, j)[1];
            // skala szerint be allitjuk a hue-t es meg nezzuk 
            // milyen szaturacioval kapnank a kivant kept
            if ((hue < 75 && hue > 20) && saturation > 75) {
                // a kepek masolasa elobb csak a szolo, majd a kek is
                dest.at<Vec3b>(i, j) = orig.at<Vec3b>(i, j);
                dest2.at<Vec3b>(i, j) = orig.at<Vec3b>(i, j)[2];
            }
        }
    }
    //megjelenitjuk a kepeket
    imshow("eredeti", orig);
    imshow("csak_szolo", dest);
    imshow("kek_szolo", dest2);
    waitKey();

    return 0;
}
//-------------------------------------------------------------
//CIE Lab
//1.FELADAT:

#include <iostream>
#include <opencv2/core.hpp>    // osztalyok, strukturak, alapveto funkciok
#include <opencv2/highgui.hpp> // felulet
#include <opencv2/imgproc.hpp> // kepfeld. konyvtar, gyakran kell majd

using namespace std;
using namespace cv;

int main() {
    // beolvassuk a kepet
    Mat orig = imread("szolo.jpg", IMREAD_COLOR);
    // atmeretezzuk az otodere, mert tul nagy a kep
    resize(orig, orig, Size(orig.cols / 5, orig.rows / 5));

    Mat lab;
    //konvertaljuk BGR-bol Lab-ra
    cvtColor(orig, lab, COLOR_BGR2Lab);

    //megjelenitjuk a kepernyon
    imshow("eredeti", orig);
    imshow("lab", lab);
    waitKey();

    return 0;
}

//_________________________________________________________
*/
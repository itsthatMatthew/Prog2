#include <iostream>
#include <sstream>
#include <string>
#include "memtrace.h"
#include "gtest_lite.h"
#include "generikus_matrix.hpp"

// Generikus fuggveny, tetszoleges algoritmussal
template<class T>
T foo(size_t i, size_t j)
{
    return (T) i * j;
}

// generikus funktor, tetszoleges algoritmussal
template<class T> class Foo
{
private:
    T m_a;
public:
    Foo(T a) : m_a(a) {}
    T operator()(size_t i, size_t j) { return (i + j) * m_a; }
}; // struct Foo

int main(int argc, char const *argv[])
{
    GTINIT(std::cin);

    // Konstruktorok tesztjei (mind)
    std::cout << std::endl << "Konstruktorok tesztjei (mind)" << std::endl;
    TEST(Konstruktor_teszt, kivetel)
        EXPECT_ANY_THROW(Matrix<int>(0, 0, 0));
    END
    TEST(Konstruktor_teszt, inicializalo_lista)
        Matrix<int> matrix({{1, 2, 3}, {4, 5, 6}});
        EXPECT_EQ(2u, matrix.sorszam());
        EXPECT_EQ(3u, matrix.oszlopszam());
        int a = 1;
        for (size_t i = 1; i <= 2; i++)
        for (size_t j = 1; j <= 3; j++)
            EXPECT_EQ(a++, matrix(i, j));
    END
    // Ha ezek jol mukodnek, a teszteket mar keszithetjuk ezekkel
    TEST(Konstruktor_teszt, param_nelkul)
        Matrix<int> m_np;
        EXPECT_EQ(0u, m_np.sorszam());
        EXPECT_EQ(0u, m_np.oszlopszam());
        EXPECT_ANY_THROW(m_np(1, 1));
    END
    TEST(Konstruktor_teszt, parameteres)
        Matrix<int> m_p(2, 3, 6);
        Matrix<int> teszt = {{6, 6, 6}, {6, 6, 6}};
        EXPECT_EQ(teszt, m_p);
    END
    TEST(Konstruktor_teszt, fv_pointer)
        Matrix<int> m_fvp(2, 3, &foo);
        Matrix<int> teszt = {{1, 2, 3}, {2, 4, 6}};
        EXPECT_EQ(teszt, m_fvp);
    END
    TEST(Konstruktor_teszt, funktor)
        Foo<int> funktor(7);
        Matrix<int> m_funk(2, 3, funktor);
        Matrix<int> teszt = {{14, 21, 28}, {21, 28, 35}};
        EXPECT_EQ(teszt, m_funk);
    END

    // Masolas (konstruktor&operator)
    std::cout<< "Masolas";
    TEST(Konstruktor_teszt, masolo_konstruktor)
        Matrix<int> matrix(2, 3, 6);
        Matrix<int> m_matrix = matrix;
        EXPECT_EQ(matrix, m_matrix);
    END
    TEST(Konstruktor_teszt, ertekado_operator)
        Matrix<int> matrix(2, 3, 6);
        Matrix<int> m_matrix;
        m_matrix = matrix;
        EXPECT_EQ(matrix, m_matrix);
    END
    TEST(Konstruktor_teszt, tipuskonverzio)
        Matrix<int> matrix(2, 3, 6);
        Matrix<double> m_matrix = (Matrix<double>) matrix;
        EXPECT_EQ(matrix, m_matrix);
    END

    // Mezok elerese, hibakezelese
    std::cout << std::endl << "Mezok elerese, hibakezelese" << std::endl;
    TEST(Mezok_kezelese, fuggveny_eleres)
        Matrix<int> matrix(1, 1, 1);
        EXPECT_EQ(1, matrix.mezo(1, 1));
    END
    TEST(Mezok_kezelese, operator_eleres)
        Matrix<int> matrix(1, 1, 1);
        EXPECT_EQ(1, matrix(1, 1));
    END
    TEST(Mezok_kezelese, konstans)
        const Matrix<int> matrix(1, 1, 1);
        EXPECT_EQ(1, matrix(1, 1));
    END
    TEST(Mezok_kezelese, kivetelek)
        Matrix<int> matrix(1, 1, 1);
        EXPECT_ANY_THROW(matrix.mezo(0, 0));
        EXPECT_ANY_THROW(matrix(0, 0));
        EXPECT_ANY_THROW(matrix(2, 2));
    END
    TEST(Mezok_kezelese, iras)
        Matrix<int> matrix(1, 1, 1);
        matrix(1, 1) = 2;
        EXPECT_EQ(2, matrix(1, 1));
    END

    // Logikai operatorok tesztelese
    std::cout << std::endl << "Logikai operatorok tesztje" << std::endl;
    TEST(Logikai, ==)
        Matrix<int> m1 = {{1, 2, 3}, {4, 5, 6}};
        Matrix<int> m2 = {{1, 2, 3}, {4, 5, 6}};
        EXPECT_TRUE(m1 == m2);
        EXPECT_FALSE(m1 != m2);
    END
    TEST(Logikai, !=)
        Matrix<int> m1 = {{1, 2, 3}, {4, 5, 6}};
        Matrix<int> m2 = {{6, 5, 4}, {3, 2, 1}};
        EXPECT_FALSE(m1 == m2);
        EXPECT_TRUE(m1 != m2);
    END
    TEST(Logikai, kivetel)
        Matrix<int> m1 = {{1, 2, 3}, {4, 5, 6}};
        Matrix<int> m2(1);
        EXPECT_ANY_THROW(m1 == m2);
    END

    // Iteratorok tesztje
    std::cout << std::endl << "Iteratorok tesztje" << std::endl;
    TEST(Iterator_teszt, vegigiteralas)
        Matrix<int> matrix(2, 3, 6);
        Matrix<int> teszt = {{4, 4, 4}, {4, 4, 4}};
        for (Matrix<int>::sor_iterator sor = matrix.begin(); sor != matrix.end(); sor++)
        for (Matrix<int>::sor_iterator::mezo_iterator mezo = sor.begin(); mezo != sor.end(); mezo++)
            *mezo = 4;
        EXPECT_EQ(teszt, matrix);
    END

    // Matrixmuveletek
    std::cout << std::endl << "Matrixmuveletek tesztje" << std::endl;
    TEST(Matrixmuveletek_teszt, +)
        Matrix<int> m1(2, 3, 6);
        Matrix<int> m2(2, 3, 4);
        Matrix<int> teszt(2, 3, 10);
        EXPECT_EQ(teszt, m1+m2);
    END
    TEST(Matrixmuveletek_teszt, -)
        Matrix<int> m1(2, 3, 6);
        Matrix<int> m2(2, 3, 4);
        Matrix<int> teszt(2, 3, 2);
        EXPECT_EQ(teszt, m1-m2);
    END
    TEST(Matrixmuveletek_teszt, *)
        Matrix<int> m1(2, 3, 6);
        Matrix<int> m2(3, 2, 4);
        Matrix<int> teszt1(2, 2, 72);
        Matrix<int> teszt2(3, 3, 48);
        EXPECT_EQ(teszt1, m1*m2);
        EXPECT_EQ(teszt2, m2*m1);
        EXPECT_ANY_THROW(m1*m1);
    END
    TEST(Matrixmuveletek_teszt, skalar*)
        Matrix<int> matrix(2, 3, 4);
        Matrix<int> teszt(2, 3, 8);
        EXPECT_EQ(teszt, matrix*2);
        EXPECT_EQ(teszt, 2*matrix);
    END

    // Tobbi matrixmuvelet
    std::cout << std::endl << "Egyeb matrixon vegezheto muveletek" << std::endl;
    TEST(Matrixmuveletek_teszt, GaussEliminacio (Linearis egyenletrendszer megoldasa))
        Matrix<float> matrix = {{2, 1, -1, 8}, {-3, -1, 2, -11}, {-2, 1, 2, -3}};
        Matrix<float> teszt = {{1, 0, 0, 2}, {0, 1, 0, 3}, {0, 0, 1, -1}};
        EXPECT_EQ(teszt, Matrix<float>::GaussEliminacio(matrix, 3));
    END
    TEST(Matrixmuveletek_teszt, EgysegMatrix)
        Matrix<int> matrix = Matrix<int>::EgysegMatrix(3);
        Matrix<int> teszt = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
        EXPECT_EQ(teszt, matrix);
    END
    TEST(Matrixmuveletek_teszt, Transzponalt)
        Matrix<int> matrix = {{1, 2, 3}, {4, 5, 6}};
        Matrix<int> teszt = {{1, 4}, {2, 5}, {3, 6}};
        EXPECT_EQ(teszt, matrix.Transzponalt());
        EXPECT_EQ(matrix, matrix.Transzponalt().Transzponalt());
    END
    TEST(Matrixmuveletek_teszt, Inverz)
        Matrix<float> matrix = {{2, 3}, {2, 2}};
        Matrix<float> teszt = {{-1, 3.0/2}, {1, -1}};
        EXPECT_EQ(teszt, matrix.Inverz());
        EXPECT_EQ(Matrix<float>::EgysegMatrix(2), matrix * matrix.Inverz());
        matrix(1, 2) = 2;
        EXPECT_ANY_THROW(matrix.Inverz());
        matrix.Mellefuz({{1}, {1}});
        EXPECT_ANY_THROW(matrix.Inverz());
    END
    TEST(Matrixmuveletek_teszt, Rang)
        Matrix<float> matrix = {{1, 2, 3}, {0, 2, 2}, {1, 4, 5}};
        EXPECT_EQ(size_t(2), matrix.Rang());
    END

    // Sor/oszlopmuveletek
    std::cout << std::endl << "Sor- es oszlopmuveletek" << std::endl;
    TEST(Matrixmuveletek_teszt, Mellefuz)
        Matrix<int> matrix = {{1, 2}, {4, 5}, {7, 8}};
        Matrix<int> melle = {{3}, {6}, {9}};
        Matrix<int> teszt = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
        EXPECT_EQ(teszt, matrix.Mellefuz(melle));
    END
    TEST(Matrixmuveletek_teszt, Alafuz)
        Matrix<int> matrix = {{1, 2, 3}, {4, 5, 6}};
        Matrix<int> ala = {{7, 8, 9}};
        Matrix<int> teszt = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
        EXPECT_EQ(teszt, matrix.Alafuz(ala));
    END
    TEST(Matrixmuveletek_teszt, Alafuz)
        Matrix<int> matrix = {{1, 2, 3}, {4, 5, 6}};
        Matrix<int> teszt = {{2, 4, 6}, {4, 5, 6}};
        EXPECT_EQ(teszt, matrix.SorSzoroz(1, 2));
    END
    TEST(Matrixmuveletek_teszt, SorSzoroz)
        Matrix<int> matrix = {{1, 2, 3}, {4, 5, 6}};
        Matrix<int> teszt = {{2, 4, 6}, {4, 5, 6}};
        EXPECT_EQ(teszt, matrix.SorSzoroz(1, 2));
    END
    TEST(Matrixmuveletek_teszt, SorTorol)
        Matrix<int> matrix = {{1, 2}, {3, 4}, {5, 6}};
        Matrix<int> teszt = {{1, 2}, {5, 6}};
        EXPECT_EQ(teszt, matrix.SorTorol(2));
    END
    TEST(Matrixmuveletek_teszt, SorCserel)
        Matrix<int> matrix = {{1, 2}, {3, 2}, {5, 6}};
        Matrix<int> teszt = {{5, 6}, {3, 2}, {1, 2}};
        EXPECT_EQ(teszt, matrix.SorCserel(1, 3));
    END
    TEST(Matrixmuveletek_teszt, OszlopSzoroz)
        Matrix<int> matrix = {{1, 2}, {3, 2}, {5, 6}};
        Matrix<int> teszt = {{2, 2}, {6, 2}, {10, 6}};
        EXPECT_EQ(teszt, matrix.OszlopSzoroz(1, 2));
    END
    TEST(Matrixmuveletek_teszt, OszlopTorol)
        Matrix<int> matrix = {{1, 2, 3}, {4, 5, 6}};
        Matrix<int> teszt = {{1, 3}, {4, 6}};
        EXPECT_EQ(teszt, matrix.OszlopTorol(2));
    END
    TEST(Matrixmuveletek_teszt, OszlopCserel)
        Matrix<int> matrix = {{1, 2, 3}, {4, 5, 6}};
        Matrix<int> teszt = {{3, 2, 1}, {6, 5, 4}};
        EXPECT_EQ(teszt, matrix.OszlopCserel(1, 3));
    END
    TEST(Matrixmuveletek_teszt, ReszMatrix)
        Matrix<int> matrix = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
        Matrix<int> teszt = {{5, 6}, {8, 9}};
        EXPECT_EQ(teszt, matrix.ReszMatrix(2,2, 3,3));
    END

    // Matrixok kiiratasa/beolvasasa
    std::cout << std::endl << "Matrixok kiiratasa es beolvasasa" << std::endl;
    TEST(Matrix_kiir_beolv, Print)
        Matrix<int> mp = {{11, 12}, {21, 22}};
        std::stringstream stream;
        mp.Print("Matrix", stream);
        std::string teszt = "Matrix\nR2x2\n _\t\t\t_ \n| \t11\t12\t |\n|_\t21\t22\t_|\n";
        EXPECT_EQ(teszt, stream.str());
    END
    TEST(Matrix_kiir_beolv, <<)
        Matrix<int> matrix = {{11, 12}, {21, 22}};
        std::stringstream stream;
        stream << matrix;
        std::string teszt = "R2x2\n _\t\t\t_ \n| \t11\t12\t |\n|_\t21\t22\t_|";
        EXPECT_EQ(teszt, stream.str());
    END
    TEST(Matrix_kiir_beolv, >>)
        Matrix<int> teszt = {{11, 12}, {21, 22}};
        Matrix<int> matrix;
        std::string str = "R2x2 11 12 21 22";
        std::stringstream stream(str);
        stream >> matrix;
        EXPECT_EQ(teszt, matrix);
    END

    GTEND(std::cerr);

    return 0;
}

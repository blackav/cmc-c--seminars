/*
 * пример, показывающий фазы компиляции: анализ, только затем оптимизация
 */

struct A
{
    A(int a) {}
};

struct B
{
    B(const A& b) {}
};

int main()
{
    B b{1};  // 1 -> A(int) -> B(const A&)

    /*
      здесь возникнет ошибка компиляции, так как требуется выполнить два пользовательских преобразования:
      B c = B(A(1));
    */
    B c = 1; // 1 -> A(int) -> B(const A&) -> B(const B&)

    // любое из преобразований, записанное явно, делает пример снова корректным
    B d = B(1);   // неявно 1 -> A(int)

    B e = A(1);   // неявно B(A)

    B f = B(A(1));

    /*
      все примеры выше идентичны с точки зрения генерируемого кода, так как компилятор обязан выполнять устранение лишнего копирования
      (copy elision optimization)
    */
}

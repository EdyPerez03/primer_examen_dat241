class Program
{
    static void Main(string[] args)
    {
        var calculadora = new Calculadora();

       
        Console.WriteLine("Introduce una expresión infija:");
        string infix = Console.ReadLine();
        double resultadoInfix = calculadora.EvaluarInfix(infix);
        Console.WriteLine($"Resultado infijo: {resultadoInfix}");

       
        Console.WriteLine("Introduce una expresión prefija:");
        string prefijo = Console.ReadLine();
        double resultadoPrefijo = calculadora.EvaluarPrefijo(prefijo);
        Console.WriteLine($"Resultado prefijo: {resultadoPrefijo}");
    }
}

using System;
using System.Data;

namespace CalculadoraWeb
{
    public class Calculadora
    {
        public double EvaluarExpresion(string expresion)
        {
            // Usar DataTable para evaluar la expresión
            var table = new DataTable();
            var result = table.Compute(expresion, string.Empty);
            return Convert.ToDouble(result);
        }

        // Método para evaluar expresiones prefijas (a implementar)
        public double EvaluarPrefijo(string expresion)
        {
            // Implementa la lógica para evaluar expresiones prefijas aquí
            // Podrías usar una pila para ayudar en la evaluación
            throw new NotImplementedException("Evaluar expresiones prefijas no está implementado.");
        }
    }
}

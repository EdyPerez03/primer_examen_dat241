using System;
using System.Collections.Generic;

public class Calculadora
{
   
    public double EvaluarInfix(string expresion)
    {
        var valores = new Stack<double>();
        var operadores = new Stack<char>();
        int i = 0;

        while (i < expresion.Length)
        {
            if (char.IsDigit(expresion[i]))
            {
                string numero = "";
                while (i < expresion.Length && (char.IsDigit(expresion[i]) || expresion[i] == '.'))
                {
                    numero += expresion[i];
                    i++;
                }
                valores.Push(double.Parse(numero));
            }
            else if (expresion[i] == '(')
            {
                operadores.Push(expresion[i]);
                i++;
            }
            else if (expresion[i] == ')')
            {
                while (operadores.Count > 0 && operadores.Peek() != '(')
                {
                    valores.Push(Evaluar(operadores.Pop(), valores.Pop(), valores.Pop()));
                }
                operadores.Pop(); 
                i++;
            }
            else if (EsOperador(expresion[i]))
            {
                while (operadores.Count > 0 && Prioridad(operadores.Peek()) >= Prioridad(expresion[i]))
                {
                    valores.Push(Evaluar(operadores.Pop(), valores.Pop(), valores.Pop()));
                }
                operadores.Push(expresion[i]);
                i++;
            }
            else
            {
                i++;
            }
        }

        while (operadores.Count > 0)
        {
            valores.Push(Evaluar(operadores.Pop(), valores.Pop(), valores.Pop()));
        }

        return valores.Pop();
    }

    public double EvaluarPrefijo(string expresion)
    {
        var valores = new Stack<double>();
        var tokens = expresion.Trim().Split(' ');

        for (int i = tokens.Length - 1; i >= 0; i--)
        {
            if (double.TryParse(tokens[i], out double num))
            {
                valores.Push(num);
            }
            else if (EsOperador(tokens[i][0]))
            {
                // Asegúrate de que hay suficientes operandos en la pila
                if (valores.Count < 2)
                {
                    throw new InvalidOperationException("Expresión prefija no válida.");
                }

                double valor1 = valores.Pop();
                double valor2 = valores.Pop();
                valores.Push(Evaluar(tokens[i][0], valor1, valor2));
            }
            else
            {
                throw new InvalidOperationException($"Token no válido: {tokens[i]}");
            }
        }

        // Asegúrate de que haya un solo resultado al final
        if (valores.Count != 1)
        {
            throw new InvalidOperationException("Expresión prefija no válida.");
        }

        return valores.Pop();
    }


    private bool EsOperador(char c) => c == '+' || c == '-' || c == '*' || c == '/';

    private int Prioridad(char operador)
    {
        return operador switch
        {
            '+' => 1,
            '-' => 1,
            '*' => 2,
            '/' => 2,
            _ => 0,
        };
    }

    private double Evaluar(char operador, double a, double b)
    {
        return operador switch
        {
            '+' => a + b,
            '-' => a - b,
            '*' => a * b,
            '/' => a / b,
            _ => throw new ArgumentException("Operador no válido")
        };
    }
}

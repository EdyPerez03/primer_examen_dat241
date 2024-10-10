using Microsoft.AspNetCore.Mvc;

namespace CalculadoraWeb.Controllers
{
    [ApiController]
    [Route("[controller]")]
    public class CalculadoraController : ControllerBase
    {
        // Acción para mostrar tu nombre
        [HttpGet("nombre")]
        public ActionResult<string> ObtenerNombre()
        {
            return "Edy Germán Pérez Calcina";
        }

        // Acción para sumar
        [HttpGet("sumar")]
        public ActionResult<double> Sumar(double a, double b)
        {
            return a + b;
        }

        // Acción para restar
        [HttpGet("restar")]
        public ActionResult<double> Restar(double a, double b)
        {
            return a - b;
        }

        // Acción para multiplicar
        [HttpGet("multiplicar")]
        public ActionResult<double> Multiplicar(double a, double b)
        {
            return a * b;
        }

        // Acción para dividir
        [HttpGet("dividir")]
        public ActionResult<double> Dividir(double a, double b)
        {
            if (b == 0)
            {
                return BadRequest("No se puede dividir entre cero.");
            }
            return a / b;
        }
    }
}

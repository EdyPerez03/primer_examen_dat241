using System;
using System.Drawing;
using System.Windows.Forms;

namespace ej9_deteccionbordes
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            // Ruta absoluta a la imagen
            string imagePath = @"C:\Users\59171\Documents\Programacion\examen_241\ej9_deteccionbordes\ej9_deteccionbordes\ej9_deteccionbordes\images\imgprueba_9.jpg";

            // Comprobar si el archivo de imagen existe
            if (!System.IO.File.Exists(imagePath))
            {
                MessageBox.Show("El archivo de imagen no se encuentra en la ruta especificada.");
                return;
            }

            Bitmap originalImage = null;

            try
            {
                // Cargar la imagen en el Bitmap directamente
                originalImage = new Bitmap(imagePath);
            }
            catch (Exception ex)
            {
                MessageBox.Show("Error al cargar la imagen: " + ex.Message);
                return; // Salir si hay un error al cargar la imagen
            }

            // Verificar si la imagen está correctamente cargada
            if (originalImage == null)
            {
                MessageBox.Show("No se ha cargado ninguna imagen.");
                return;
            }

            // Asignar la imagen original al PictureBox
            pictureBox1.Image = originalImage;

            // Crear un bitmap para la imagen procesada
            Bitmap edgeImage = new Bitmap(originalImage.Width, originalImage.Height);

            // Aplicar filtro de Sobel para detección de bordes
            for (int y = 1; y < originalImage.Height - 1; y++)
            {
                for (int x = 1; x < originalImage.Width - 1; x++)
                {
                    // Obtener el valor de intensidad de gris de los píxeles vecinos
                    Color pixel1 = originalImage.GetPixel(x - 1, y - 1);
                    Color pixel2 = originalImage.GetPixel(x, y - 1);
                    Color pixel3 = originalImage.GetPixel(x + 1, y - 1);
                    Color pixel4 = originalImage.GetPixel(x - 1, y);
                    Color pixel5 = originalImage.GetPixel(x + 1, y);
                    Color pixel6 = originalImage.GetPixel(x - 1, y + 1);
                    Color pixel7 = originalImage.GetPixel(x, y + 1);
                    Color pixel8 = originalImage.GetPixel(x + 1, y + 1);

                    // Filtro Sobel en direcciones X y Y
                    int gx = (-1 * pixel1.R) + (1 * pixel3.R) + (-2 * pixel4.R) + (2 * pixel5.R) + (-1 * pixel6.R) + (1 * pixel8.R);
                    int gy = (-1 * pixel1.R) + (-2 * pixel2.R) + (-1 * pixel3.R) + (1 * pixel6.R) + (2 * pixel7.R) + (1 * pixel8.R);

                    // Calcular magnitud
                    int g = (int)Math.Sqrt((gx * gx) + (gy * gy));

                    // Limitar los valores a 0-255
                    g = Math.Min(Math.Max(g, 0), 255);

                    // Asignar el nuevo valor de color
                    edgeImage.SetPixel(x, y, Color.FromArgb(g, g, g));
                }
            }

            // Mostrar la imagen con los bordes detectados en el PictureBox2
            pictureBox2.Image = edgeImage;
        }
    }
}

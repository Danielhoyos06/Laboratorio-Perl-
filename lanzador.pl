#!/usr/bin/perl

#**************************************************************
#                       Pontificia Universidad Javeriana
#     Materia: Sistemas Operativos
#     Fichero: lanzador fichero por lotes
#         Descripcion: Automatizacion de ejecuciones para obtencion de 30 
#                       resultados de ejecuciones de los benchmarks de distintos sabores 
#                       con el proposito de hacer experimentos de caracter cientifico (fiablilidad y presion)
#****************************************************************/

# Obtiene el directorio actual y lo guarda en la variable $Path
$Path = `pwd`;
chomp($Path);  # Elimina el salto de línea al final del string obtenido por `pwd`

# Lista con los nombres de los ejecutables que se van a probar
@Nombre_Ejecutable = ("mm_clasica");

# Tamaños de las matrices con los que se va a probar
@Size_Matriz = (500, 1000);

# Cantidad de hilos que se utilizarán en las pruebas
@Num_Hilos = (1, 2);

# Número de repeticiones por cada combinación de parámetros
$Repeticiones = 30;

# Bucle para recorrer cada ejecutable
foreach $Nombre_Ejecutable (@Nombre_Ejecutable) {

    # Bucle para recorrer cada tamaño de matriz
    foreach $size (@Size_Matriz) {

        # Bucle para recorrer cada número de hilos
        foreach $hilo (@Num_Hilos) {

            # Construye el nombre del archivo donde se almacenarán los resultados
            $file = "$Path/$Nombre_Ejecutable-" . $size . "-Hilos-" . $hilo . ".dat";

            # Ejecuta la prueba $Repeticiones veces
            for ($i = 0; $i < $Repeticiones; $i++) {

                # Ejecuta el programa y redirige la salida al archivo .dat correspondiente
                system("$Path/$Nombre_Ejecutable $size $hilo >> $file");

                # Imprime en consola el comando que se está ejecutando
                printf("$Path/$Nombre_Ejecutable $size $hilo \n");
            }

            # Comentado: línea que sería para cerrar archivo si se usara filehandle
            # close($file);

            # Variable acumuladora que nunca se declara antes, pero se usa para contar combinaciones (opcional)
            $p = $p + 1;
        }
    }
}

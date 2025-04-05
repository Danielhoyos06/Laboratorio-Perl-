#!/usr/bin/perl

#**************************************************************
#                       Pontificia Universidad Javeriana
#     Materia: Sistemas Operativos
#     Fichero: lanzador fichero por lotes
#         Descripcion: Automatizacion de ejecuciones para obtencion de 30 
#                       resultados de ejecuciones de los benchmarks de distintos sabores 
#                       con el proposito de hacer experimentos de caracter cientifico (fiablilidad y presion)
#****************************************************************/

$Path = `pwd`;
chomp($Path);


@Nombre_Ejecutable = ("mm_clasica");

@Size_Matriz = (500, 1000);

@Num_Hilos = (1,2);

$Repeticiones = 4;

foreach $Nombre_Ejecutable (@Nombre_Ejecutable) {
    foreach $size (@Size_Matriz) {
        foreach $hilo (@Num_Hilos) {

            $file = "$Path/$Nombre_Ejecutable-".$size."-Hilos-".$hilo.".dat";

            for ($i = 0; $i < $Repeticiones; $i++) {

                system("$Path/$Nombre_Ejecutable $size $hilo  >> $file");

                printf("$Path/$Nombre_Ejecutable $size $hilo \n");
            }

            #close($file);

            $p = $p + 1;
        }
    }
}


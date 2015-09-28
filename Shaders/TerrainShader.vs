
 //Zmienne otrzymywane dla każdego wierzchołka

attribute vec3 inPosition;  // Pozycja wierzchołka
attribute vec3 inNormal;  // Wektory kierunkowe trójkąta
attribute vec2 inTexcoord;  // Koordynanty tekstury

uniform mat4 MVP;   //Macierz modelu * macierz widoku * macierz projekcji 
uniform mat3 ModelMatrix; //Macierz modelu

// varying - Zmienna współdzielona z programem fragmentów (.ps).

varying vec3 Normal;  //normalne siatki (wektory kierunkowe)
varying vec2 ScaledUV; //Powiększona siatka UV dla tekstur trawy, ziemi, itp (by były większe)

void main()
{
	ScaledUV = inTexcoord*100.0;
	gl_TexCoord[0].st = inTexcoord;  //Wysyłanie koordynantów tekstury do programu fragmentu (.ps)
	Normal = normalize (ModelMatrix * inNormal);  //Mnożenie wektorów kierunkowych wierzchołków przez macierz modelu (rotacja)
	
	gl_Position = MVP * vec4(inPosition, 1.0);  //Mnożenie pozycji wierzchołków przez macież MVP  (Ustawianie ich na ekranie)
}

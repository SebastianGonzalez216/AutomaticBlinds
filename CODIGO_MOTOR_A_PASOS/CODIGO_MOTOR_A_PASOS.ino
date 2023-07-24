

// Ajuste de movimiento de motor a grados

#include <Separador.h>

Separador s;

int retardo=5;          // Tiempo de retardo en milisegundos (Velocidad del Motor)
int dato_rx;            // Dato recibido en grados
int dato_mov;
int numero_pasos = 0;   // Valor en grados donde se encuentra el motor (estado inicial)
String leeCadena;       // Almacena la cadena de datos recibida

String movimiento;
String grados;



void setup() // Metodo Setup en el que programamos el estado del Arduino
{          
Serial.begin(9600);     // inicializamos el puerto serie a 9600 (utilizado en este caso)
pinMode(11, OUTPUT);    // Pin 11 en modo salida (conectar a IN4)
pinMode(10, OUTPUT);    // Pin 10 en modo salida (conectar a IN3)
pinMode(9, OUTPUT);     // Pin 9 en modo salida (conectar a IN2)
pinMode(8, OUTPUT);     // Pin 8 en modo salida (conectar a IN1)



}

//--------------------------------------------------------------------------------------------

  void loop()         // Metodo bucle
  {





    
    while (Serial.available()) // Mientras este disponible la conexion Serial
    {    
    delay(retardo);            // Tiempo de espera
    char c  = Serial.read();   // Lee los caracteres ingresados en el monitor Serial   <---- este se enviara a traves de java
    leeCadena += c;             // Convierte la suma de caracteres a cadena de caracteres
    }  
    
 
     if (leeCadena.length()>0) // Si el largo de la cadena es mayor a 0
      {       
         movimiento = s.separa(leeCadena, ',', 0);
         grados =s.separa(leeCadena, ',', 1);

         Serial.println("El movimiento seleccionado es " + movimiento);
         Serial.println("El movimiento seleccionado es " + grados);
         
      dato_rx = grados.toInt();   // Convierte Cadena de caracteres a enteros, ahora en dato_rx
      dato_mov = movimiento.toInt();
      
      Serial.print(dato_rx);         // Imprime valor en Grados 
      Serial.println(" Grados");     // Imprime "grados" y un salto de linea
      delay(retardo);
      dato_rx = (dato_rx * 1.4222222222); // Ajuste de 512 pasos a los 360 grados (depende de cada motor, en este caso 512/260 = 1.4222222222)
      }  

         while (dato_rx>numero_pasos)   // Giro hacia la izquierda en grados
         {   
            if (dato_mov ==1)    // Si movimiento es igual a 1
            {
            paso_simple_izq();  // Llamada de metodo
            numero_pasos = numero_pasos + 1;
            }
            else if (dato_mov==2)   // Si movimiento es igual a 2
            {
            paso_doble_izq();  
            numero_pasos = numero_pasos + 1;
            }
            else if (dato_mov==3)  // Si movimiento es igual a 3
            {
            paso_medio_izq();  
            numero_pasos = numero_pasos + 1; 
            }
                    
         
         }
         
         
        while (dato_rx<numero_pasos)   // Giro hacia la derecha en grados
        {   
            if (dato_mov ==1)   // Si movimiento es igual a 1
            {
            paso_simple_der();  // Llamada de metodo
            numero_pasos = numero_pasos -1;
            }
            else if (dato_mov==2)  // Si movimiento es igual a 2
            {
            paso_doble_der(); 
            numero_pasos = numero_pasos -1; 
            }
            else if (dato_mov==3)  // Si movimiento es igual a 3
            {
            paso_medio_der();  
            numero_pasos = numero_pasos -1;
            }                   // LLamada de metodo
        
        }

        
            leeCadena = "";   // Inicializamos la cadena de caracteres recibidos 
            apagado();         // LLamada de metodo
  }  





//-----------------------------------------------------------------------------------------------------------------------------------
//El estado low apaga y el estado high enciende, cada pin esta conectado a una respectiva bobina, este motor cuenta con 4 bobinas
//las que se encenderan y apagaran para poder realizar los pasos


void SerialEvent()
{

}









void paso_doble_der(){         // Pasos dobles a la derecha
 digitalWrite(11, LOW); 
 digitalWrite(10, LOW);  
 digitalWrite(9, HIGH);  
 digitalWrite(8, HIGH);  
   delay(retardo); 
 digitalWrite(11, LOW); 
 digitalWrite(10, HIGH);  
 digitalWrite(9, HIGH);  
 digitalWrite(8, LOW);  
   delay(retardo); 
 digitalWrite(11, HIGH); 
 digitalWrite(10, HIGH);  
 digitalWrite(9, LOW);  
 digitalWrite(8, LOW);  
  delay(retardo); 
 digitalWrite(11, HIGH); 
 digitalWrite(10, LOW);  
 digitalWrite(9, LOW);  
 digitalWrite(8, HIGH);  
  delay(retardo);  
}

void paso_doble_izq() {        // Pasos dobles a la izquierda
 digitalWrite(11, HIGH); 
 digitalWrite(10, HIGH);  
 digitalWrite(9, LOW);  
 digitalWrite(8, LOW);  
  delay(retardo); 
 digitalWrite(11, LOW); 
 digitalWrite(10, HIGH);  
 digitalWrite(9, HIGH);  
 digitalWrite(8, LOW);  
  delay(retardo); 
 digitalWrite(11, LOW); 
 digitalWrite(10, LOW);  
 digitalWrite(9, HIGH);  
 digitalWrite(8, HIGH);  
  delay(retardo); 
 digitalWrite(11, HIGH); 
 digitalWrite(10, LOW);  
 digitalWrite(9, LOW);  
 digitalWrite(8, HIGH);  
  delay(retardo); 
}


void paso_simple_der() {        // Pasos simples a la derecha
 digitalWrite(11, LOW); 
 digitalWrite(10, LOW);  
 digitalWrite(9, LOW);  
 digitalWrite(8, HIGH);  
   delay(retardo); 
 digitalWrite(11, LOW); 
 digitalWrite(10, LOW);  
 digitalWrite(9, HIGH);  
 digitalWrite(8, LOW);  
   delay(retardo); 
 digitalWrite(11, LOW); 
 digitalWrite(10, HIGH);  
 digitalWrite(9, LOW);  
 digitalWrite(8, LOW);  
  delay(retardo); 
 digitalWrite(11, HIGH); 
 digitalWrite(10, LOW);  
 digitalWrite(9, LOW);  
 digitalWrite(8, LOW);  
  delay(retardo); 
}


void paso_simple_izq() {        // Pasos simples a la izquierda
 digitalWrite(11, HIGH); 
 digitalWrite(10, LOW);  
 digitalWrite(9, LOW);  
 digitalWrite(8, LOW);  
   delay(retardo); 
 digitalWrite(11, LOW); 
 digitalWrite(10, HIGH);  
 digitalWrite(9, LOW);  
 digitalWrite(8, LOW);  
   delay(retardo); 
 digitalWrite(11, LOW); 
 digitalWrite(10, LOW);  
 digitalWrite(9, HIGH);  
 digitalWrite(8, LOW);  
  delay(retardo); 
 digitalWrite(11, LOW); 
 digitalWrite(10, LOW);  
 digitalWrite(9, LOW);  
 digitalWrite(8, HIGH);  
  delay(retardo); 
}


void paso_medio_der() {        // Pasos medios a la derecha
 digitalWrite(11, LOW); 
 digitalWrite(10, LOW);  
 digitalWrite(9, LOW);  
 digitalWrite(8, HIGH);  
   delay(retardo); 
 digitalWrite(11, LOW); 
 digitalWrite(10, LOW);  
 digitalWrite(9, HIGH);  
 digitalWrite(8, HIGH);  
   delay(retardo); 
 digitalWrite(11, LOW); 
 digitalWrite(10, LOW);  
 digitalWrite(9, HIGH);  
 digitalWrite(8, LOW);  
  delay(retardo); 
 digitalWrite(11, LOW); 
 digitalWrite(10, HIGH);  
 digitalWrite(9, HIGH);  
 digitalWrite(8, LOW);  
  delay(retardo); 

 digitalWrite(11, LOW); 
 digitalWrite(10, HIGH);  
 digitalWrite(9, LOW);  
 digitalWrite(8, LOW);  
   delay(retardo); 
 digitalWrite(11, HIGH); 
 digitalWrite(10, HIGH);  
 digitalWrite(9, LOW);  
 digitalWrite(8, LOW);  
   delay(retardo); 
 digitalWrite(11, HIGH); 
 digitalWrite(10, LOW);  
 digitalWrite(9, LOW);  
 digitalWrite(8, LOW);  
  delay(retardo); 
 digitalWrite(11, HIGH); 
 digitalWrite(10, LOW);  
 digitalWrite(9, LOW);  
 digitalWrite(8, HIGH);  
  delay(retardo); 
}

void paso_medio_izq() {        // Pasos medios a la izquierda
 digitalWrite(11, HIGH); 
 digitalWrite(10, LOW);  
 digitalWrite(9, LOW);  
 digitalWrite(8, LOW);  
   delay(retardo); 
 digitalWrite(11, HIGH); 
 digitalWrite(10, HIGH);  
 digitalWrite(9, LOW);  
 digitalWrite(8, LOW);  
   delay(retardo); 
 digitalWrite(11, LOW); 
 digitalWrite(10, HIGH);  
 digitalWrite(9, LOW);  
 digitalWrite(8, LOW);  
  delay(retardo); 
 digitalWrite(11, LOW); 
 digitalWrite(10, HIGH);  
 digitalWrite(9, HIGH);  
 digitalWrite(8, LOW);  
  delay(retardo); 

 digitalWrite(11, LOW); 
 digitalWrite(10, LOW);  
 digitalWrite(9, HIGH);  
 digitalWrite(8, LOW);  
   delay(retardo); 
 digitalWrite(11, LOW); 
 digitalWrite(10, LOW);  
 digitalWrite(9, HIGH);  
 digitalWrite(8, HIGH);  
   delay(retardo); 
 digitalWrite(11, LOW); 
 digitalWrite(10, LOW);  
 digitalWrite(9, LOW);  
 digitalWrite(8, HIGH);  
  delay(retardo); 
 digitalWrite(11, HIGH); 
 digitalWrite(10, LOW);  
 digitalWrite(9, LOW);  
 digitalWrite(8, HIGH);  
  delay(retardo); 
}
        
void apagado() {         // Apagado del Motor
 digitalWrite(11, LOW); 
 digitalWrite(10, LOW);  
 digitalWrite(9, LOW);  
 digitalWrite(8, LOW);  
 }

#define boton_record 2
#define rgb 4
#define tiempo 125
#define led A0
#define bocina A1
#define sensor A4
#define boton_play A5

//Variables de entrada
short int botones[] = {13,12,11,10,9,8,7};
boolean record;
boolean play;
boolean v_boton1;
boolean v_boton2;
boolean v_boton3;
boolean v_boton4;
boolean v_boton5;
boolean v_boton6;
boolean v_boton7;
boolean v_sensor;
boolean v_boton;
//Variables del rgb y led
short int color = 0;
int pin_rgb[] = {6,5,3}; //[0] r, [1] g, [2] b
//Otras variables
float notas[] = {440.00, 493.883, 523.251, 587.330, 659.255, 698.456, 783,991};
boolean on = LOW;
boolean bandera = HIGH;
//Lista para almacenar las notas MIDI
int lista[50];
short int nota;
short int i = 0;

void setup() {
  //Inicializar entradas
  for (i = 6; i >= 0; i--){
    pinMode(botones[i], INPUT);
  }
  pinMode(sensor, INPUT);
  //Inicializar salidas
  pinMode(rgb, OUTPUT);
  delay(20);

  //Establecer la comunicación serial para el puerto
  Serial.begin(9600);

  //Establecer la interrupción para comenzar a grabar y dejar de hacerlo
  attachInterrupt(0,Turnon, RISING);

  //Por si acaso, apagar los led
  digitalWrite(rgb, LOW);
  digitalWrite(led, LOW);
  delay(20);

}

void loop() {
  record = digitalRead(boton_record);
  play = digitalRead(boton_play);
  delay(50);

  //Si se aprieta el botón de record, comienza la grabación
  //El led rojo se encience
  if (record == HIGH && on == HIGH && bandera == HIGH){
    //Borrar los datos anteriores de la lista
    for (i = 49; i >= 0; i--){
      lista[i] = 0;
    }

    //Encender el led rojo
    bandera = LOW;
    analogWrite(led, 150);
    digitalWrite(rgb, LOW);

    //"Grabar" las notas en la lista
    Grabar(); 
    delay(20);
    
  } else if (play == HIGH && bandera == HIGH){
    //Reproduce las notas contenidas en la lista
    digitalWrite(rgb, HIGH);
    analogWrite(led, LOW);

    for (i = 0; i < 50; i++){
      for (int j = 2; j >= 0; j--){
        color = random(250);
        analogWrite(pin_rgb[i], color);
        color = 0;
      }
      noteOn(0x90, lista[i], 100);
      delay(400);
      noteOn(0x90, lista[i], 0);
      delay(125);
      //Si hay dos elementos seguidos en cero, ya no hay más sonidos
      //Y deja de reproducir la música
      if (lista[i-1] == 0 && lista[i] == 0){
        break;
      }
    }
    
  }

  bandera = HIGH;
  digitalWrite(rgb, LOW);
  analogWrite(led, LOW);
  delay(50);
}

/*Esta función permite "grabar". Guarda los valores 
 ingresados por el usuario por medio del teclado en un
 arreglo
*/
void Grabar(){
  i = 0;
  while (on != LOW){
    v_boton1 = digitalRead(botones[0]);
    v_boton2 = digitalRead(botones[1]);
    v_boton3 = digitalRead(botones[2]);
    v_boton4 = digitalRead(botones[3]);
    v_boton5 = digitalRead(botones[4]);
    v_boton6 = digitalRead(botones[5]);
    v_boton7 = digitalRead(botones[6]);
    v_sensor = digitalRead(sensor);
    v_boton = digitalRead(boton_record);
    delay(20);

    if (v_boton1 == HIGH || v_boton2 == HIGH || v_boton3 == HIGH || v_boton4 == HIGH || v_boton5 == HIGH || v_boton6 == HIGH || v_boton7 == HIGH || v_sensor == HIGH){
      if (v_boton1 == HIGH){          //LA4
        tone(bocina, notas[0], tiempo);
        nota = 69;
      } else if (v_boton2 == HIGH){   //SI4
        tone(bocina, notas[1], tiempo);
        nota = 71;
      } else if (v_boton3 == HIGH){   //DO5
        tone(bocina, notas[2], tiempo);
        nota = 72;
      } else if (v_boton4 == HIGH){   //RE5
        tone(bocina, notas[3], tiempo);
        nota = 74;
      } else if (v_boton5 == HIGH){   //MI5
        tone(bocina, notas[4], tiempo);
        nota = 76;
      } else if (v_boton6 == HIGH){   //FA5
        tone(bocina, notas[5], tiempo);
        nota = 77;
      } else if (v_boton7 == HIGH){   //SOL5
        tone(bocina, notas[6], tiempo);
        nota = 79;
      } else if (v_sensor == HIGH){   //SOL5
        tone(bocina, 620, tiempo);
        nota = 1;
      }
  
      lista[i] = nota;
      i++;
      delay(400);
    } else if (v_boton == HIGH){
        on = LOW;
      }
    
  }  
}

void noteOn(int comando, int altura, int velocidad) {
  // Aquí enviamos uno a uno los bytes del mensaje MIDI
  Serial.write(comando);
  Serial.write(altura);
  Serial.write(velocidad);
}

//La secuencia de interrupción enciende y apaga on
void Turnon(){  
  on = !on; 
}

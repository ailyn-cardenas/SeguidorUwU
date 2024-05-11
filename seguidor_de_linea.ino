// Definición pines de habilitación para el control de la velocidad conectados a pines digitales
int VelocidadMotor1 = 6; 
int VelocidadMotor2 = 5;

// Definición de los pines de control de giro de los motores tanto izquierdo como derecho
int Motor1A = 13; 
int Motor1B = 12;  
int Motor2C = 11; 
int Motor2D = 10; 

//Definición de los pines de Sensores infrarrojo - izquierdo y derecho
int infraPin  = 2;    //izquierdo
int infraPin1 = 4;      //derecho

// Variables para la captura de los valores: 0-blanco y 1-negro
int valorInfra = 0;  
int valorInfra1 = 0;  

// Configuración inicial
void setup() {
  Serial.begin(9600);
  
  delay(1000);

  // Establecemos modo de los pines de los sensores infrarrojo estan leyendo fondo blanco o negro
  pinMode(infraPin, INPUT);    
  pinMode(infraPin1, INPUT);

  // Establecemos modo de los pines del control de motores 
  pinMode(Motor1A,OUTPUT);
  pinMode(Motor1B,OUTPUT);
  pinMode(Motor2C,OUTPUT);
  pinMode(Motor2D,OUTPUT);
  pinMode(VelocidadMotor1, OUTPUT);
  pinMode(VelocidadMotor2, OUTPUT);

  // Configuramos los dos motores a velocidad 150/255 velocidades la maxima es de 155
  analogWrite(VelocidadMotor1, 150); 
  analogWrite(VelocidadMotor2, 150);  

  // Configuramos sentido de giro (parado)
  digitalWrite(Motor1A, LOW);
  digitalWrite(Motor1B, LOW);
  digitalWrite(Motor2C, LOW);
  digitalWrite(Motor2D, LOW);
}

// Ejecución contínua
void loop() {
  // Leemos el valor de los infrarrojo: 0 - fondo claro y 1 - línea negra
  valorInfra = digitalRead(infraPin);   
  valorInfra1 = digitalRead(infraPin1);

  Serial.println(valorInfra);
  Serial.println(valorInfra1);
         
  // Cuatro escenarios: De frente (ambos sensores estan sobre el margen blanco     
  if(valorInfra == 0 && valorInfra1 == 0){
    Serial.println("Ninguno en linea");
    
    // Modificamos sentido de giro de los motores
    digitalWrite(Motor1A, HIGH);
    digitalWrite(Motor2D, HIGH);
    delay(20);                      
    digitalWrite(Motor1A, LOW);
    digitalWrite(Motor2D,LOW);
    delay(20);                     
  }

  // El robot encuentra línea negra con el infrarrojo derecho
  if(valorInfra == 0 && valorInfra1 == 1){  
    Serial.println("Derecho en linea");
    
    // Modificamos sentido de giro de los motores
    digitalWrite(Motor1A, LOW);
    digitalWrite(Motor2D,LOW);
    delay(25);
    digitalWrite(Motor1A, HIGH);
    digitalWrite(Motor2D,LOW);
    delay(20);
  }

  // El robot encuentra línea negra con el infrarrojo izquierdo 
  if(valorInfra == 1 && valorInfra1 == 0){ 
    Serial.println("Izquierdo en linea");
    
    // Modificamos sentido de giro de los motores
    digitalWrite(Motor1A,LOW);
    digitalWrite(Motor2D, LOW);
    delay(25);
    digitalWrite(Motor1A,LOW);
    digitalWrite(Motor2D, HIGH);
    delay(20);
  }

  // Los dos sensores infrarrojos encuentran una línea negra, significa el final del circuito
  if(valorInfra == 1 && valorInfra1 == 1){ 
    Serial.println("Ambos en linea");
    
    // Paramos los motores 
    digitalWrite(Motor1A, LOW);
    digitalWrite(Motor1B, LOW);
    digitalWrite(Motor2C, LOW);
    digitalWrite(Motor2D, LOW);
  }
}

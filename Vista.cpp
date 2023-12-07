#include "Vista.h"
#include <iostream>

Vista::Vista(){
    //ingresa el tipo de la fuete
    if(!fuente.loadFromFile("C:/Windows/Fonts/COOPBL.TTF")){
        //si no la encuentra avisa
        std::cout << "no cargo";
    }
    setlocale(LC_ALL, "spanish");
    //le asigna un tamaño, color y fuente al texto que se presenta por pantalla
    texto.setCharacterSize(50);
    texto.setFillColor(sf::Color::Black);
    texto.setFont(fuente);

    //al vector lineas le asigana 4 espacios puesto que son los cuadrados que
    //existen por linea
    linea.resize(4);
    for(int j = 0; j < 2; j++) {
        for (int i = 0; i < 4; i++) {
            //asinga  el tamaño,color y posicion que van a tener los cuadros estaticos
            //osea los que contiene la palabra inicial y final
            linea[i].setSize(sf::Vector2f(100.f, 100.f));
            linea[i].setFillColor(sf::Color(196, 196, 196));
            linea[i].setPosition(i * (100.f + 12.f) + 75.f,  0.f);
        }
        //añade una liena al vector cuadrados estaticos
        cuadrosEstaticos.push_back(linea);
    }

   //inicializa la linea visible en 0 puesto que desde esta se va a empezar a visualizar
    inicioVisible = 0;

    //añade un espacio vacio a las palabras para facilitar su manupulacion
    palabras.push_back("");

    //añade las palabras inicial y final que se va a tener durante el juego
    palabrasEstaticas.push_back("LIMA");
    palabrasEstaticas.push_back("LOMO");


    for(int i = 0; i < 4; i++) {
        //modidica el color, los bordes y los bordes de los cuadrados añadir una linea nueva cada
        //que el usuario toque enter
        linea[i].setFillColor(sf::Color::Transparent);
        linea[i].setOutlineColor(sf::Color(196, 196, 196));
        linea[i].setOutlineThickness(2.f);
    }
    //añade la primer liena a cuadrados para que el usuario mire donde esta escribiendo
    cuadrados.push_back(linea);

    //inicializa el color que debe tener la caja de error
    cajaError.setFillColor(sf::Color(255, 0, 0));

    //se le añade los atributos necesarios para el texto de erro
    textoError.setFont(fuente);
    textoError.setCharacterSize(20);
    error = false;
}

void Vista::principal(){

    //asigna un tamaño a la ventana
    window.create(sf::VideoMode(600,700), "SFML Window", sf::Style::Close);

    //imprime las palabras iniciales y el primer reglon de escritura
    imprimir();

    while(window.isOpen()){
        while (window.pollEvent(eventos)) {
            //si se toca la x de la pantalla se cierra
            if (eventos.type == sf::Event::Closed) {
                window.close();
            }

            if (eventos.type == sf::Event::TextEntered) {
                //si se toca alguna tecla se llama a la funcion escritura encargadad de guardar
                //lo escrito por el usuario y a si poder manipular esta informacion
                escritura();
            }
            if (eventos.type == sf::Event::MouseWheelScrolled){
                if (eventos.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
                    //verifica si se movio la rueda del mouse para poder hacer scroll
                    if (eventos.mouseWheelScroll.delta > 0 && inicioVisible > 0 && cuadrados.size() > 2) {
                        //controla desde que linea se empiza a ver siempre y cuando ya se halla exedido
                        //el limite de lineas por pantalla que son 3 lineas al mismo tiempo
                        inicioVisible--;
                        //imprime este nuevo orden de lineas
                        imprimir();
                    }
                    else if (eventos.mouseWheelScroll.delta < 0 && inicioVisible < cuadrados.size() - 3 && cuadrados.size() > 2) {
                        //hace lo mismo que el anterior if
                        inicioVisible++;
                        imprimir();
                    }
                }
            }
        }
    }
}

void Vista::escritura(){

    if (eventos.text.unicode == '\r' && palabras[palabras.size()-1].size() >= 4){
        //si el usuario le dio enter y el tamaño de la palabra es el correcto
        //se validad que cumpla las reglas de juego

        imprimir();
        if(error) {
          //si no las cumple no lo deja continuar y lo devuelve con un mensaje de error
          error = false;
          //despues de avisar errores vuelve a ser falso
          return;
        };
        //si el numero de palabras execede lo visible por pantalla se controla desde donde se deja ver al usuario
        if(palabras.size() >= 3) inicioVisible++;
        //se añade un nuevo reglon en blanco
        cambiarColorCuadro();
        palabras.push_back("");
        cuadrados.push_back(linea);
        error = true;
    }else if(eventos.text.unicode >= 97 && eventos.text.unicode <= 122 && palabras[palabras.size()-1].size() < 4 ||
                eventos.text.unicode >= 65 && eventos.text.unicode <= 90  && palabras[palabras.size()-1].size() < 4 ||
                eventos.text.unicode == 241 && palabras[palabras.size()-1].size() < 4 ||
                eventos.text.unicode == 209 && palabras[palabras.size()-1].size() < 4 ){
        //valida si el usuario toco una letra si es asi combierte el codigo de esa letra en un char y lo guarda en un string
        //solo lo deja introducir caracteres si el tamaño del string es menor a 4
        palabras[palabras.size()-1] += std::toupper(static_cast<char>(eventos.text.unicode));
        //si el usuario no esta mirando donde esta escribiendo se le posicion la vista en la casilla donde se esta realizando la accion
        if(palabras.size() > 2) inicioVisible = palabras.size()-3;
    }else if (eventos.key.code == 8){
        //si se oprime la tecla de borrar
        if (!palabras[palabras.size()-1].empty()) {
            //se valida que el string no este vacio y se borra el ultimo caracter de este
            palabras[palabras.size()-1].pop_back();
        }else if(palabras.size() > 1){
            //si el string esta vacio borramos to do un reglon para empezar a modificar el reglon anterior
            palabras.pop_back();
            cuadrados.pop_back();
            devolverColor();
            //si tenemos mas de 3 reglones en pantalla se modifica desde donde empieza a observar el usuario
            if(inicioVisible != 0) inicioVisible--;
        }
    }
    //se imprimen todos los cambios pertientes
    imprimir();
}

void Vista::cambiarColorCuadro(){
    //recorremos toda la cadena de caracteres para verificar si hay algun caracter igual a la palabra final
   for(int i = 0; i < 4; i++){
       if(palabras[palabras.size()-1][i] == palabrasEstaticas[1][i]){
           //si lo hay cambia el color de del cuadro donde esta la letra igual
           cuadrados[cuadrados.size()-1][i].setFillColor(sf::Color(110, 235, 101));
           //tambien cambia el color del cuadro donde es igual a la palabra final
           cuadrosEstaticos[1][i].setFillColor(sf::Color(15, 255, 0));
       }else if(cuadrosEstaticos[1][i].getFillColor() == sf::Color(15, 255, 0)){
           //si no es validad si el cuadro esta pintado de verde y si lo esta lo devuelve al color original
           cuadrosEstaticos[1][i].setFillColor(sf::Color(196, 196, 196));
       }
   }
}

void Vista::devolverColor(){
    for(int i = 0; i < 4; i++){
        //recorre los cuadrados y valida si aguno esta de color verda
        if(cuadrados[cuadrados.size()-1][i].getFillColor() == sf::Color(110, 235, 101)){
            //si lo esta lo cambia a color trasparente para dejarlo como es originalmente
            cuadrados[cuadrados.size()-1][i].setFillColor(sf::Color::Transparent);
        }
        if(palabras.size() != 1) {
            //valida si palabras tiene mas de dos palabras dentro
            if(palabras[palabras.size()-2][i] == palabrasEstaticas[1][i])
            {
                //si tiene mas de dos valida la antepenultima sigue teniendo coincidencias con la palabra final
                //y le cambia el color a los cuadros de la palabra final
                cuadrosEstaticos[1][i].setFillColor(sf::Color(15, 255, 0));
            }else if(cuadrosEstaticos[1][i].getFillColor() == sf::Color(15, 255, 0)){
                // si la letra no es igual valida si esta de color verde y si lo esta lo cambia a su color original
                cuadrosEstaticos[1][i].setFillColor(sf::Color(196, 196, 196));
            }
        }else if(cuadrosEstaticos[1][i].getFillColor() == sf::Color(15, 255, 0)){
            //por ultimo palabras solo tiene una palabra o no tiene palabras cambia el color de los cuadros de la palbra final que esten en verde a su color original
            cuadrosEstaticos[1][i].setFillColor(sf::Color(196, 196, 196));
        }
    }
}


void Vista::imprimirCuadrado(){
    //inicializa un contador y la canitadad de lineas que se van a imprimir
    //Contador sirve para calcular la posicion en la que debe ir cada cuadro de forma automatica
    int cont = 2;
    int lineasVisibles = 3;
    for (int i = inicioVisible; i < inicioVisible + lineasVisibles && i < cuadrados.size(); i++) {
        for(int j = 0; j < 4; j++) {
            if(palabras[i].size() == j){
                //si estamos en el cuadro donde se va a escribir se cambia el color a color negro para indicar
                //al usuario donde se encuntra realizando los cambios
                cuadrados[i][j].setOutlineColor(sf::Color::Black);
            }
            //operecion encargada de calcular la posicion en pantalla para que to do se mire pulcro
            cuadrados[i][j].setPosition(cuadrados[i][j].getPosition().x,  100.f * cont * 1.2f - 70.f);
            //dibuja cada cuadro en la posicon respectiva
            window.draw(cuadrados[i][j]);
            //vuelve a cambiar el color del cuadro al color neutro
            cuadrados[i][j].setOutlineColor(sf::Color(196, 196, 196));
            if(palabras[i].size() > j){
                //se le añade lo que tiene que ser mostrado por pantalla a texto que en este caso es un char
                texto.setString(palabras[i][j]);
                //se calcula la posicion en la que debe ir este caracter para que quede dentro de cada cuadrado
                texto.setPosition(cuadrados[i][j].getPosition().x + 30.f, cuadrados[i][j].getPosition().y + 17.f);
                //imprime el texto
                window.draw(texto);
            }

        }
        //aumenta el contador para saber en que cudro se va y asi poder posicionarlo de forma perfecta
        cont++;
    }
}

void Vista::imprimirCuadradosEstaticos(){
    //contador para poder posicionar los cuadros de mejor manera en pantalla
    int cont = 1;
    for(int i = 0; i < 2; i++) {
        for (int j = 0; j < 4; j++) {
            //calcula la posicion en la quedebe ir cada cuadrado para que se mire bien por pantalla
            cuadrosEstaticos[i][j].setPosition(cuadrosEstaticos[i][j].getPosition().x,  100.f * cont * 1.2f - 70.f);
            //dibuja en pantalla cada cuadrado
            window.draw(cuadrosEstaticos[i][j]);
            //se le asigna a la variable texto un caracter para poder posicionarlo en su cuadro respectivo
            texto.setString(palabrasEstaticas[i][j]);
            //se le asigna la posicion en la que debe ir
            texto.setPosition(cuadrosEstaticos[i][j].getPosition().x + 30.f, cuadrosEstaticos[i][j].getPosition().y + 17.f);
            //se dibuja en la pantalla el caracter
            window.draw(texto);
        }
        //calcula en que posicion debe ir la palabra final para asi poderse adaptar a la cantidad de palabras en la pantalla
        cont = (cuadrados.size() < 3) ?(cuadrados.size()+2) :(5);
    }
}

void Vista::imprimirErrores(){

    if(error /*funcion que me diga si se cambio mas de una letra*/){
        //si se ha cambiado mas de una palabra salta un error
        //se modifica el tamaño de la caja para ajustarse mejor al texto emergente
        cajaError.setSize(sf::Vector2f(250,40));
        //se le calcula la pocision con ayuda del tamaño de la ventana y asi poder centrarlo de manera mas precisa
        cajaError.setPosition((window.getSize().x - cajaError.getSize().x)/2,window.getSize().y - 60);
        //se añade el texto del error para indicar al usuario que esta realizando mal
        textoError.setString("Cambia solo una letra");
        //se obtiene el tamaño que ocupa por pantalla el texto para asi poder centrarlo mejor en el cuadro anteriormente echo
        sf::FloatRect bounds = textoError.getLocalBounds();
        textoError.setPosition(cajaError.getPosition().x + (cajaError.getSize().x - bounds.width) / 2,
                               cajaError.getPosition().y + (cajaError.getSize().y - bounds.height) / 2 - 7);
        //se indica que existe un error para no permitir el funcionamiento del programa hasta que se solucione
        error = true;
    }else if(prueba /*funcion que me diga si la palabra existe*/) {
        //se añade el texto del error
        textoError.setString("Por favor ingrese una palabra existente");
        //se obtiene la caja que delimita el texto
        sf::FloatRect bounds = textoError.getLocalBounds();
        //se utiliza esta caja para darle el tamaño a la caja de error
        cajaError.setSize(sf::Vector2f(bounds.width + 30,40));
        //se le calcula la pocision con ayuda del tamaño de la ventana y asi poder centrarlo de manera mas precisa
        cajaError.setPosition((window.getSize().x - cajaError.getSize().x)/2,window.getSize().y - 60);
        //se posiciona el texto en la mitdad del cuadrado
        textoError.setPosition(cajaError.getPosition().x + (cajaError.getSize().x - bounds.width) / 2,
                               cajaError.getPosition().y + (cajaError.getSize().y - bounds.height) / 2 - 7);

        error = true;
    }
    if(error){
        //Se dibuja tanto la caja como el texto en la pantalla si hay errores
        window.draw(cajaError);
        window.draw(textoError);
    }
}

void Vista::imprimir(){
    //se limpia to do lo existente en la pantalla y asi no generar conflictos
    window.clear(sf::Color::White);
    //se imprimen los cuadros estaticos que contiene las palabras inicial y final
    imprimirCuadradosEstaticos();
    //se imprimen los cuadros y el texto que va en ellos
    imprimirCuadrado();
    if(palabras[palabras.size()-1].size() == 4 && eventos.text.unicode == '\r'){
        //si se oprimio enter y el tamaño del string es de 4 letras se valida si hay errores en el string
        imprimirErrores();
    }
    //se imprime por pantalla to do lo anteriormente dibujado
    window.display();
}
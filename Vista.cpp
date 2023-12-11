#include "Vista.h"
#include <iostream>

Boton::Boton(sf::FloatRect cajaTexto){
    //acomoda el tamaño de la caja con el tamaño de la letra para que esta despues se pueda comodar de mejor manera
    caja.setSize(sf::Vector2f(cajaTexto.width+30.f,cajaTexto.height + 30.f));
    //se le pone un color trasparente por defecto para poder interactuar con el
    caja.setFillColor(sf::Color::Transparent);
    //se le agraga color a el contorno del cuadro
    caja.setOutlineColor(sf::Color(196, 196, 196));
    //se le asigna un grosor al contorno del cuadro
    caja.setOutlineThickness(2.f);
}

Boton::Boton(){
    caja.setSize(sf::Vector2f(50.f,50.f));
    caja.setPosition(10.f,10.f);
}

Vista::Vista(){
    //se utiliza para establecer la configuración regional o localización en un programa y que asi funcione la ñ

    //ingresa el tipo de la fuete
    if(!fuente.loadFromFile("C:/Windows/Fonts/COOPBL.TTF")){
        //si no la encuentra avisa
        std::cout << "no cargo";
    }
    if (!pausa.loadFromFile("../archivos/pausa.png")) {
        // Manejar el error si no se puede cargar la imagen
        std::cout << "no cargo";
    }
    //le asigna un tamaño, color y fuente al texto que se presenta por pantalla
    texto.setFillColor(sf::Color::Black);
    texto.setFont(fuente);
    texto.setCharacterSize(50);
    //se le añade los atributos necesarios a los textos secundarios
    textoSecundario.setFont(fuente);
    textoSecundario.setCharacterSize(20);
    textoSecundario.setFillColor(sf::Color::Black);
    //se ponen las variables principales sin con los requisitos necesarios para empezar el juego
    reseteo();
    //no hay errores
    error = false;
    //no hay ganadores
    winer = false;
    //inicializa el color que debe tener la caja de error
    cajaError.setFillColor(sf::Color(255, 0, 0));
    colicion = true;
    guardar = false;
    cargar = false;
    pausado = false;
    loser = false;
}

void Vista::reseteo(){
    //borra todos los vectores que se han creado para empezar un juego con to do limpio
    palabras.clear();
    cuadrados.clear();
    palabrasEstaticas.clear();
    cuadrosEstaticos.clear();
    linea.clear();
    botones.clear();

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
    int difultad = 10;
    //añade las palabras inicial y final que se va a tener durante el juego
    //palabrasEstaticas = logica.mostarPalabrasInicioYFin(difultad);
    if(!cargar) {
        palabrasEstaticas.push_back("LIMA");
        palabrasEstaticas.push_back("LOMO");
    }

    for(int i = 0; i < 4; i++) {
        //modidica el color, los bordes y los bordes de los cuadrados añadir una linea nueva cada
        //que el usuario toque enter
        linea[i].setFillColor(sf::Color::Transparent);
        linea[i].setOutlineColor(sf::Color(196, 196, 196));
        linea[i].setOutlineThickness(2.f);
    }
    //añade la primer liena a cuadrados para que el usuario mire donde esta escribiendo
    cuadrados.push_back(linea);
}

void Vista::insertarPalabras(const std::vector<std::string>& npalabras){
    reseteo();

    palabras = npalabras;
    int cont = 0;
    palabrasEstaticas.push_back(palabras[0]);
    palabrasEstaticas.push_back(palabras[palabras.size()-1]);

    palabras.erase(palabras.begin());
    palabras.erase(palabras.end());

    for(int i = 0; i < palabras.size()-1; i++) {
        for (int j = 0; j < 4; j++) {
            //modidica el color, los bordes y los bordes de los cuadrados añadir una linea nueva cada
            //que el usuario toque enter
            if(palabras[i][j] == palabrasEstaticas[1][j]) {
                //si lo hay cambia el color de del cuadro donde esta la letra igual
                cuadrados[i][j].setFillColor(sf::Color(110, 235, 101));
                //tambien cambia el color del cuadro donde es igual a la palabra final
                cuadrosEstaticos[1][j].setFillColor(sf::Color(15, 255, 0));
            }
            else{
                linea[cont].setFillColor(sf::Color::Transparent);
                cuadrosEstaticos[1][j].setFillColor(sf::Color(196, 196, 196));
            }
            linea[cont].setOutlineColor(sf::Color(196, 196, 196));
            linea[cont].setOutlineThickness(2.f);

        }
        //añade la primer liena a cuadrados para que el usuario mire donde esta escribiendo
        cuadrados.push_back(linea);
        cont = (cont < 4) ?(cont++) :(0);
    }
    inicioVisible = (palabras.size() <= 3) ?(0) :(palabras.size() - 3);
}

void Vista::principal(){

    botones.push_back(Boton());
    botones[0].caja.setTexture(&pausa);
    botones[0].cajaColision = botones[0].caja.getGlobalBounds();
    //imprime las palabras iniciales y el primer reglon de escritura
    imprimir();
    //Se ejecuta mientras no se halla ganado el juego
    while(!winer){
        while (window.pollEvent(eventos)) {
            //si se toca la x de la pantalla se cierra
            if (eventos.type == sf::Event::Closed) {
                window.close();
                return;
            }
            if(colisionConBoton()){
                if(click() == 0){
                    pausado = true;
                    botones.clear();
                    return;
                }
            }
            if (eventos.type == sf::Event::TextEntered) {
                //si se toca alguna tecla se llama a la funcion escritura encargadad de guardar
                //lo escrito por el usuario y a si poder manipular esta informacion
                escritura();
            }
            if (eventos.type == sf::Event::MouseWheelScrolled) {
                if (eventos.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
                    //verifica si se movio la rueda del mouse para poder hacer scroll
                    if (eventos.mouseWheelScroll.delta > 0 && inicioVisible > 0 && cuadrados.size() > 2) {
                        //controla desde que linea se empiza a ver siempre y cuando ya se halla exedido
                        //el limite de lineas por pantalla que son 3 lineas al mismo tiempo
                        inicioVisible--;
                        //imprime este nuevo orden de lineas
                        imprimir();
                    } else if (eventos.mouseWheelScroll.delta < 0 && inicioVisible < cuadrados.size() - 3 &&
                    cuadrados.size() > 2) {
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

    if (eventos.text.unicode == '\r' && palabras[palabras.size()-1].size() >= 4 && !winer){
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

        //se añade un nuevo reglon en blanco
        cambiarColorCuadro();
        if(winer){
            //si el usuario gana se borra lo que creado para asi estar listos por si quiere volver a jugar
            reseteo();
            //sale de la funcion puesto que no es necesario que se repita mas despues de conseguir un ganador
            return;
        }else {
            //si no hay ganador se continua con la logica de añadir una nueva fila
            if (palabras.size() >= 3) inicioVisible++;
            palabras.push_back("");
            cuadrados.push_back(linea);
        }

    }else if((eventos.text.unicode >= 97 && eventos.text.unicode <= 122 && palabras[palabras.size()-1].size() < 4) ||
            (eventos.text.unicode >= 65 && eventos.text.unicode <= 90  && palabras[palabras.size()-1].size() < 4) ||
            (eventos.text.unicode == 241 && palabras[palabras.size()-1].size() < 4) ||
            (eventos.text.unicode == 209 && palabras[palabras.size()-1].size() < 4) ){
        //valida si el usuario toco una letra si es asi combierte el codigo de esa letra en un char y lo guarda en un string
        //solo lo deja introducir caracteres si el tamaño del string es menor a 4
        palabras[palabras.size()-1] += std::toupper(static_cast<char>(eventos.text.unicode));
        //si el usuario no esta mirando donde esta escribiendo se le posicion la vista en la casilla donde se esta realizando la accion
        if(palabras.size() > 2) inicioVisible = palabras.size()-3;
    }else if (eventos.key.code == 8 && !winer){
        //si se oprime la tecla de borrar
        if (!palabras[palabras.size()-1].empty()) {
            //se valida que el string no este vacio y se borra el ultimo caracter de este
            palabras[palabras.size()-1].pop_back();
        }else if(palabras.size() > 1){
            //si el string esta vacio borramos to do un reglon para empezar a modificar el reglon anterior
            palabras.pop_back();
            cuadrados.pop_back();
            //y cambiamos el color de los cuadros de esa linea y de los cuadros de la palabra final
            devolverColor();
            //si tenemos mas de 3 reglones en pantalla se modifica desde donde empieza a observar el usuario
            if(inicioVisible != 0) inicioVisible--;
        }
    }
    //se imprimen todos los cambios pertientes
    imprimir();

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

    bool diferente = (palabras.size() <= 1) ?( logica.difiereUnaLetra(palabrasEstaticas[0], palabras[0]))
            :(logica.difiereUnaLetra(palabras[palabras.size()-2], palabras[palabras.size()-1]));
   if(!diferente){
        //si se ha cambiado mas de una palabra salta un error
        //se modifica el tamaño de la caja para ajustarse mejor al texto emergente
        cajaError.setSize(sf::Vector2f(250,40));
        //se le calcula la pocision con ayuda del tamaño de la ventana y asi poder centrarlo de manera mas precisa
        cajaError.setPosition((window.getSize().x - cajaError.getSize().x)/2,window.getSize().y - 60);
        //se añade el texto del error para indicar al usuario que esta realizando mal
        textoSecundario.setString("Cambia solo una letra");
        //se obtiene el tamaño que ocupa por pantalla el texto para asi poder centrarlo mejor en el cuadro anteriormente echo
        sf::FloatRect bounds = textoSecundario.getLocalBounds();
        textoSecundario.setPosition(cajaError.getPosition().x + (cajaError.getSize().x - bounds.width) / 2,
                               cajaError.getPosition().y + (cajaError.getSize().y - bounds.height) / 2 - 7);
        //se indica que existe un error para no permitir el funcionamiento del programa hasta que se solucione
        error = true;
    }else if(!logica.esPalabraValida(palabras[palabras.size() - 1])){
        cout << "dentro de if" << endl;
        //se añade el texto del error
        textoSecundario.setString("Por favor ingrese una palabra existente");
        //se obtiene la caja que delimita el texto
        sf::FloatRect bounds = textoSecundario.getLocalBounds();
        //se utiliza esta caja para darle el tamaño a la caja de error
        cajaError.setSize(sf::Vector2f(bounds.width + 30,40));
        //se le calcula la pocision con ayuda del tamaño de la ventana y asi poder centrarlo de manera mas precisa
        cajaError.setPosition((window.getSize().x - cajaError.getSize().x)/2,window.getSize().y - 60);
        //se posiciona el texto en la mitdad del cuadrado
        textoSecundario.setPosition(cajaError.getPosition().x + (cajaError.getSize().x - bounds.width) / 2,
                               cajaError.getPosition().y + (cajaError.getSize().y - bounds.height) / 2 - 7);
        //indica que si hay un error en la linea
        error = true;
    }
    if(error){
        //Se dibuja tanto la caja como el texto en la pantalla si hay errores
        window.draw(cajaError);
        window.draw(textoSecundario);
    }
}

void Vista::imprimir(){
    //se limpia to do lo existente en la pantalla y asi no generar conflictos
    window.clear(sf::Color::White);
    window.draw(botones[0].caja);
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

void Vista::cambiarColorCuadro() {
    //para saber si es igual a la palabra final
    int igual = 0;
    //recorremos toda la cadena de caracteres para verificar si hay algun caracter igual a la palabra final
    for(int i = 0; i < 4; i++){
        if(palabras[palabras.size()-1][i] == palabrasEstaticas[1][i]){
            //si lo hay cambia el color de del cuadro donde esta la letra igual
            cuadrados[cuadrados.size()-1][i].setFillColor(sf::Color(110, 235, 101));
            //tambien cambia el color del cuadro donde es igual a la palabra final
            cuadrosEstaticos[1][i].setFillColor(sf::Color(15, 255, 0));
            igual++;
        }else if(cuadrosEstaticos[1][i].getFillColor() == sf::Color(15, 255, 0)){
            //si no es validad si el cuadro esta pintado de verde y si lo esta lo devuelve al color original
            cuadrosEstaticos[1][i].setFillColor(sf::Color(196, 196, 196));
        }
    }
    if(igual == 4){
        //si se llega a tener 4 coincidencias indica que la palbra escitra por el usuario es igual a la palabra final por ende gano
        winer = true;
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

void Vista::menuGeneral(const std::string& titulo, const std::vector<std::string>& opciones){
    window.clear(sf::Color::White);
    //titulo de la pantalla
    textoSecundario.setString(titulo);
    //ponemos el titulo del menu un poco mas grande
    textoSecundario.setCharacterSize(60.f);
    //lo pocisionamos en la mitad de la pantalla pero lo desplazamos un poco hacia arriba puesto que interrumpia los botones
    textoSecundario.setPosition((window.getSize().x - textoSecundario.getLocalBounds().width)/2, ((window.getSize().y - textoSecundario.getLocalBounds().height)/2) - (opciones.size())*50.f );
    //imptimimos el texto
    window.draw(textoSecundario);
    //opciones que van a existir en el menu
    //Se arregla el tamaño de la letra
    textoSecundario.setCharacterSize(20.f);
    for(int i = 0; i < opciones.size(); i++){
        //se agrega el texto del boton
        textoSecundario.setString(opciones[i]);
        //todos los cambios se realizan siempre y cuando se este creando el vector de botones
        if(botones.size() < opciones.size()) {
            //se crea un nuevo objeto de botones y se le pasa el tamaño del texto para si ajueste de mejor manera
            botones.push_back(Boton(textoSecundario.getLocalBounds()));
            //se pone en mitad de la pantalla para mejor estetica
            if(guardar){
                botones[i].caja.setPosition((window.getSize().x - botones[i].caja.getSize().x)/2 + (i+1)*botones[i].caja.getSize().x - 170.f,
                                            ((window.getSize().y - botones[i].caja.getSize().y)/2) + 100.f);
            }else{
                botones[i].caja.setPosition((window.getSize().x - botones[i].caja.getSize().x)/2,
                                            ((window.getSize().y - botones[i].caja.getSize().y)/2)+ (i+1)*65.f- 40.f*(opciones.size()));
            }
            //se iguala la caja de coliciones nueva a la del cuadro que contiene el texto para que este cambie cuando lo valide
            botones[i].cajaColision = botones[i].caja.getGlobalBounds();
        }
        //si el boton se ecuentra seleccionado y se deja de seleccionar cambia de color
        if( botones[i].caja.getFillColor() == sf::Color(196, 196, 196) && !colicion) {
            botones[i].caja.setFillColor(sf::Color::Transparent);
        }
        //se pone el texto en donde se pusieron anteriormente los botoenes y se calcula para que quede en el centro del boton
        textoSecundario.setPosition(botones[i].caja.getPosition().x + (botones[i].caja.getSize().x - textoSecundario.getLocalBounds().width) / 2,
                                    botones[i].caja.getPosition().y + (botones[i].caja.getSize().y - textoSecundario.getLocalBounds().height) / 2 - 7);
        //se dibuja lo necesario
        window.draw(botones[i].caja);
        window.draw(textoSecundario);

    }
    //se muestra to do por pantalla
    window.display();
}

void Vista::menuInicio(){

    //si no hay ganador
    if(colisionConBoton()){
        //y si coliciono con algun boton entonces se vuelve a imprimir t odo pero con diferente color
        if(colicion){
            menuGeneral("Weaver", {"Empezar", "Cargar partida", "Salir"});
            //nos dice que se cambio el color
            colicion = false;
        }
        switch (click()) {
            //si hace click en alguna de las opciones limpia los botones para que se puedan crear de manera correcta en el siguiente menu
            case 0:
                botones.clear();
                //llama a donde se va ejecutarel juego
                principal();
                return;
            case 1:
                //llama a la funciond donde se va a cargar una partida
                botones.clear();
                cargar = true;
                return;
            case 2:
                //salir lo saca del programa
                window.close();
                return;
            case -1:
                //no se preciono le click
                return;
        }
    }else if (!colicion){
        //se cambia el color a trasparente
        menuGeneral("Weaver", {"Empezar", "Cargar partida", "Salir"});
        colicion = true;
    }
}

void Vista::menuWinnerOrLoser(){
    //misma logica que el menu de inicio
    if(botones.empty()){
        reseteo();
        if(loser){
            menuGeneral("Loser", {"Ver solucion Optima", "Volver"});
        }else if(winer) {
            menuGeneral("Winer", {"Ver solucion Optima", "Volver"});
        }
    }
    if (colisionConBoton()) {
        if(colicion) {
            if(loser){
                menuGeneral("Loser", {"Ver solucion Optima", "Volver"});
            }else if(winer) {
                menuGeneral("Winer", {"Ver solucion Optima", "Volver"});
            }
            colicion = false;
        }
        switch (click()) {
            case 0:
                botones.clear();
                palabras.clear();
                insertarPalabras(logica.encontrarCaminoMinimoPalabras(palabrasEstaticas[0], palabrasEstaticas[1]));
                winer = false;
                loser = false;
                principal();
                return;
            case 1:
                //lo devuelve al menu de inicio
                botones.clear();
                winer = false;
                loser = false;
                return;
            case -1:
                return;
        }
    } else if (!colicion) {
        cout << "entre";
        if(loser){
            menuGeneral("Loser", {"Ver solucion Optima", "Volver"});
        }else if(winer) {
            menuGeneral("Winer", {"Ver solucion Optima", "Volver"});
        }
        colicion = true;

    }
}

void Vista::menuPausa(){
    if(botones.empty()){
        menuGeneral("Pausa",{"Cotinuar", "Rendirse", "Guardar partida", "Cargar partida", "Salir"});
    }
    if (colisionConBoton()) {
        if(colicion) {
            menuGeneral("Pausa",{"Cotinuar", "Rendirse", "Guardar partida", "Cargar partida", "Salir"});
            colicion = false;
        }
        switch (click()) {
            case 0:
                botones.clear();
                pausado = false;
                principal();
                return;
            case 1:
                botones.clear();
                loser = true;
                winer = false;
                pausado = false;
                return;
            case 2:
                botones.clear();
                guardar = true;
                return;
            case 3:
                botones.clear();
                cargar = true;
                return;
            case 4:
                pausado = false;
                reseteo();
                return;
            case -1:
                //no se preciono le click
                return;
        }
    } else if (!colicion) {
        menuGeneral("Pausa",{"Cotinuar", "Rendirse", "Guardar partida", "Cargar partida", "Salir"});
        colicion = true;
    }
}

void Vista::menuCargar(){
    pausado = false;
    partidasGuardadas = logica.cargarPartida("../archivos/partidas.txt");
    if(botones.empty()){
        menuGeneral("Pausa",partidasGuardadas);
    }
    if (colisionConBoton()) {
        if(colicion) {
            menuGeneral("Pausa",partidasGuardadas);
            colicion = false;

        }
        if(clikeado > 0){
            insertarPalabras((logica.cargarPartida("../archivos/" + partidasGuardadas[clikeado])));
            cout << "entre" << endl;
            cargar = false;
        }
    } else if (!colicion) {
        menuGeneral("Pausa",partidasGuardadas);
        colicion = true;
    }
}

void Vista::menuGuardar(){
    std::string nombre;

    if(botones.empty()){
        menuGeneral("Guardando", {"Aceptar", "Cancelar"});
    }
    if (colisionConBoton()) {
        if(colicion) {
            menuGeneral("Guardando", {"Aceptar", "Cancelar"});
            colicion = false;
        }
        switch (click()) {
            case 0:
                botones.clear();
                palabras.insert(palabras.begin(),palabrasEstaticas[0]);
                palabras.push_back(palabrasEstaticas[1]);
                //logica.guardarPartida(palabras, "../archivos/hola1.txt");
                palabras.erase(palabras.begin());
                palabras.pop_back();
                guardar = false;
                return;
            case 1:
                botones.clear();
                guardar = false;
                return;
            case -1:
                //no se preciono le click
                return;
        }
    } else if (!colicion) {
        menuGeneral("Guardando", {"Aceptar", "Cancelar"});
        colicion = true;
    }


}

void Vista::menus(){
    //asigna un tamaño a la ventana
    window.create(sf::VideoMode(600,700), "SFML Window", sf::Style::Close);
    //para validar si ya se imprimio lo que esta dentro del menu para asi poder realizar los cambios de color en los botones

    menuGeneral("Weaver", {"Empezar", "Cargar partida", "Salir"});
    while(window.isOpen()) {
        while (window.pollEvent(eventos)) {
            if (eventos.type == sf::Event::Closed) {
                window.close();
            }
            if(!winer && !pausado && !cargar && !loser){
                menuInicio();
            }
            else if((winer && !pausado) || (loser && !pausado)) {

                menuWinnerOrLoser();
            }
            else if(pausado && !guardar && !cargar){
               menuPausa();
            }
            else if(guardar){
                menuGuardar();
            }
            else if(cargar) {
                menuCargar();
            }
        }
    }
}

bool Vista::colisionConBoton(){
    //recuper la poscion del mouse en pantalla
    mouse = sf::Mouse::getPosition(window);
    if(!botones.empty()) {
        //si botones no esta bacio
        for (int i = 0; i < botones.size(); i++) {
            //verifica si esta tocando la caja de colicion del cuadrado
            if (botones[i].cajaColision.contains(static_cast<float>(mouse.x), static_cast<float>(mouse.y))) {
                //le cambia el color al cuadrado
                botones[i].caja.setFillColor(sf::Color(196, 196, 196));
                //devueleve verdadero para poder cambiar el color al cuadro donde esta
                return true;
            }
        }
    }
    //no hubo colicion no hay necesidad de entrar a cambiar el color
    return false;
}

int Vista::click(){
    if (eventos.type == sf::Event::MouseButtonPressed) {
        //si se preciona el click del mouse
        if (eventos.mouseButton.button == sf::Mouse::Left) {
            //si el click fue el derecho recuper la pocision en pantalla
            mouse = sf::Mouse::getPosition(window);
            for (int i = 0; i < botones.size(); i++) {
                //valida a que boton fue
                if (botones[i].cajaColision.contains(static_cast<float>(mouse.x), static_cast<float>(mouse.y))) {
                    //devuelve el boton que se clickeo
                    clikeado = i;
                    return i;
                }
            }
        }
    }
    //no se clickeo nada;
    return -1;
}

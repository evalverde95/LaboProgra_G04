=======================
 Proyecto 1: AVL Tree
=======================

El primer proyecto consiste en la creación de una estructura de datos correspondiente a un árbol auto-balanceable, en este caso el AVL Tree, donde se implemente y pruebe el correcto funcionamiento de la misma. 

Integrantes
===========
* Ricardo Jiménez Anchía
* Daniel Meseguer Wong
* Laura Rincón Riveros
* Esteban Valverde Hernández

Documentación
=============
La doucmentación individual para cada una de las funciones utilizadas se **puede encontrar en la carpeta doc, en el archivo index.html**. En este archivo se detallan los parámetros de entrada y salida para cada una de las funciones, mientras que la guía de usuario se enfoca en dar ejemplos claros del uso de las funciones.

Guía de usuario
===============
Esta guía de usuario consta de cuatro partes principales:

* Creación y uso del proyecto.
* Complejidad experimental del algoritmo de inserción.
* Funciones.
* Pruebas.

Esta guía de usuario se enfoca en el correcto uso de los elementos y en dar una clara explicación del proyecto.

1. Creación y uso del proyecto
------------------------------
Dado que el proyecto utiliza compilación automática por medio de CMake para construir el proyecto se puede hacer uso de la siguiente secuencia de comandos en bash
::

    mkdir build
    cd build
    cmake ..
    make
    ./exe

2. Complejidad del algoritmo de inserción
-----------------------------------------
La complejidad teórica para la inserción en un árbol auto-balanceable es de :math:`O(f(n))=\log(n)`, para probar esto se realizaron inserciones en un árbol con distinta cantidad de inserciones previas (entre 100 y 100 000) y se tomó el tiempo de la última inserción, estas inserciones fueron de números aleatorios para poder obtener una muestra representativa. Los resultados de este experimento se muestran en la siguiente figura XX.


..
    Esto es un comentario, solo dejar la imagen y quitar los dos puntos arriba de esto
    . image:: ./complejidad.jpg


3. Funciones
------------

3.1. Create
~~~~~~~~~~~
Dado que la función de creación tiene el siguiente prototipo, se sabe que se recibe un puntero a la lista, un tamaño de lista y un doble puntero al nodo raíz.
El puntero del nodo raíz es doble debido a que se requiere cambiar la dirección a la que apunta.

.. code-block:: c++

    int avl_create(
        float *in_number_list, 
        int list_size,
        struct avl_node **new_root_node);

Como se observa en el siguiente ejemplo se inicializan la lista, el status y un nodo raíz (inicialmente vacío) para poder llamar al método de creación con esa lista.

.. code-block:: c++
    
    int status=AVL_SUCCESS; // Initialize status
    int list_size=3; // Define list size
    float list[3]={1,2,3}; // Create list

    struct avl_node *root=nullptr; // Initially empty root

    status=avl_create(list,list_size,&root); // Create tree

    free_tree_mem(root); //Free memory assigned to nodes

Si hubiese algún código de error el usuario podría verificarlo con la variable de status.

3.2. Insert
~~~~~~~~~~~
El insert realiza la inserción como en un bst, pero posteriormente realiza el balance según el algoritmo para el árbol AVL.

El prototipo para la función es el siguiente.

.. code-block:: c++
    
    int avl_node_add(
        float num,
        struct avl_node **new_root);

Para insertar un número, solo se debe tener una raíz y un número que se desee insertar, como en el siguiente ejemplo.

.. code-block:: c++

    int status=AVL_SUCCESS; // Initialize status
    struct *root=nullptr; // Initially empty root pointer
    status=avl_node_add(3.2f,&root); // Insert element

    free_tree_mem(root); //Free memory assigned to node

3.3. Print
~~~~~~~~~~
Para realizar una impresión que permita al usuario contrastar resultados contra resultados esperados, se debe hacer uso de un recorrido que brinde información de la forma del árbol, es decir un *pre-order* o un *post-order*, esto pues si los datos se imprimen en orden no ayudan a identificar la forma del arbol. En este caso particular se seleccionó el *pre-order traversal*.

El prototipo para la función es:

.. code-block:: c++

    int avl_print_nodes(
        struct avl_node  *in_root);

En este caso hay otra función que llama a esta llamada *avl_print* que es la que el usuario llama, pero esta lo que hace es imprimir un mensaje y posteriormente proceder con *avl_print_nodes*. Un ejemplo de uso es el siguiente.

.. code-block:: c++
    
    int status=AVL_SUCCESS; // Initialize status
    int list_size=3; // Define list size
    float list[3]={1,2,3}; // Create list

    struct avl_node *root=nullptr; // Initially empty root

    status=avl_create(list,list_size,&root); // Create the AVL tree
    avl_print_nodes(root); // Call the printing function

    free_tree_mem(root); //Free memory assigned to nodes

3.4. Maximum Element
~~~~~~~~~~
Para encontrar el elemento máximo o nodo con mayor valor en un bst, se debe recorrer completamente por todos los hijos derechos que existan, hasta llegar al último, el cual será el elemento máximo.

El prototipo para la función es:

.. code-block:: c++

    int avl_max_get(
        struct avl_node  *in_root,
        struct avl_node **max_node);

En el caso del elemento máximo, se debe inicializar un nodo vacío, y se pueden agregar valores con la función de Insert o Create, o incluso dejar el nodo vacío, para el cual se dará un mensaje de error. Luego, se utiliza la función *avl_max_get* para obtener el elemento máximo.

.. code-block:: c++
    
    int status=AVL_SUCCESS; // Initialize status
    int list_size=3; // Define list size
    float list[3]={1,2,3}; // Create list

    struct avl_node *root=nullptr; // Initially empty root
    struct avl_node *max_node; // Create node to store maximum node value 

    avl_create(list,list_size,&root); // Create tree
    status = avl_max_get(root, &max_node) // Get maximum element

    free_tree_mem(root); //Free memory assigned to nodes

3.5. Minimum Element
~~~~~~~~~~
Para encontrar el elemento mínimo o nodo con menor valor en un bst, se debe recorrer completamente por todos los hijos izquierdos que existan, hasta llegar al último, el cual será el elemento mínimo.

El prototipo para la función es:

.. code-block:: c++

    int avl_min_get(
        struct avl_node  *in_root,
        struct avl_node **min_node);

En el caso del elemento mínimo, se debe inicializar un nodo vacío, y se pueden agregar valores con la función de Insert o Create, o incluso dejar el nodo vacío, para el cual se dará un mensaje de error. Luego, se utiliza la función *avl_min_get* para obtener el elemento mínimo.

.. code-block:: c++
    
    int status=AVL_SUCCESS; // Initialize status
    int list_size=3; // Define list size
    float list[3]={1,2,3}; // Create list

    struct avl_node *root=nullptr; // Initially empty root
    struct avl_node *min_node; // Create node to store minimum node value 

    avl_create(list,list_size,&root); // Create tree
    status = avl_min_get(root, &min_node) // Get minimum element

    free_tree_mem(root); //Free memory assigned to nodes


4. Pruebas
----------
Esta sección corresponde a una descripción de cada una de las pruebas realizadas.

4.1. Create
~~~~~~~~~~~
Para la creación del árbol sí se cuenta con ambos tipos de pruebas (negativas, positivas), esto debido a que esta creación puede fallar por la inadecuada especificación del tamaño de la lista de entrada para la creación del árbol.

En síntesis se tienen los siguientes casos:

* **Positiva:** Se prueba la creación del árbol con un tamaño de lista correcto, debe devolver AVL_SUCCESS.
* **Negativa:** Se prueba la creación del árbol con un tamaño de lista 0, debe devolver AVL_INVALID_PARAM.


4.2. Print
~~~~~~~~~~
Para la comprobación de la correcta impresión de la información, se redirige el *stdout* hacia un buffer y este string se compara con un string de referencia para comprobar así la correcta impresión del árbol.
En esta prueba en particular solo existe una prueba positiva debido a que no hay manera de imprimir incorrectamente el árbol dada una raíz válida, de igual manera el único parámetro que es la raíz (una dirección de memoria) no se puede comprobar como una dirección inválida para el árbol.

De esta manera el test tiene un único caso:

* **Positiva:** Se prueba que la impresión redirigida al buffer sea la misma que la esperada para una lista ya conocida.

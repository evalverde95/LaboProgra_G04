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
La complejidad teórica para la inserción en un árbol auto-balanceable es de :math:`O(f(n))=log(n)`, para probar esto se realizaron inserciones en un árbol con distinta cantidad de inserciones previas (entre 100 y 100 000) y se tomó el tiempo de la última inserción, estas inserciones fueron de números aleatorios para poder obtener una muestra representativa. Los resultados de este experimento se muestran en la siguiente figura.


    .. image:: ./Time_100.png
        :alt: Insertion complexity
        :align: center
        
Para cada uno de los tamaños aleatorios se hacen 100 inserciones para obtener el valor de la mediana de los tiempos de una inserción. 
En este caso se elige la mediana como medida de tendencia central para amortiguar el efecto que tienen los valores atípicos sobre 
otras medidas como lo es el promedio (la mediana es insesgada).

Los resultados mostrados en la figura anterior son los resultados para una prueba específica, 
lo que quiere decir que los puntos graficados van a cambiar y el ajuste puede mejorar o empeorar, 
dependiendo de los resultados de cada prueba en particular. Lo que sí es relevante destacar es que, 
aún cuando el valor del ajuste no es bueno (R^2=48%, debido a la dispersión de los datos con respecto a la línea de tendencia), 
se puede observar que la tendencia sí se sigue. Cabe destacar que en esta tendencia lo relevante es que aún cuando la estructura
tenga muchos elementos la inserción (y demás funciones) requieran de un tiempo bajo para realizarse. Se puede observar el
amortiguamiento logarítmico que mantiene el tiempo de inserción razonablemente similar entre variedad de tamaños (inclusive los
más cercanos a 100 000).

Esta prueba se encuentra contemplada dentro de las pruebas con GTest y genera un archivo csv (dentro del directorio en que 
se crea el proyecto) que se puede utilizar para generar gráficas como la anterior o realizar algún procesamiento posterior, 
es por esto que se prefiere este formato para un posible posterior análisis o procesamiento.


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


3.3. Delete
~~~~~~~~~~~
La función de delete busca el número ingresado por el usuario y dependiendo de las ramas del nodo tomará una decisión para eliminarlo y reconectar el árbol.

El prototipo para la función es el siguiente.

.. code-block:: c++

    int avl_node_remove(
        float num,
        struct avl_node **new_root);

Para eliminar un número, es necesario un puntero a la raíz y el número que se desee eliminar, como en el siguiente ejemplo.

.. code-block:: c++

    int status=AVL_SUCCESS; // Initialize status
    int list_size=3; // Define list size
    float list[3]={1,2,3}; // Create list

    struct avl_node *root=nullptr; // Initially empty root

    status=avl_create(list,list_size,&root); // Create tree
    status=avl_node_remove(2.0,&root); // Delete element

    free_tree_mem(root); //Free memory assigned to node



3.4. Print
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

3.5. Maximum Element
~~~~~~~~~~~~~~~~~~~~
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

3.6. Minimum Element
~~~~~~~~~~~~~~~~~~~~
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

3.7. Search
~~~~~~~~~~~
La función de search busca el número ingresado por el usuario en el arbol indicado por el usuario, pasando un puntero con la direccion del nodo root.
Finalmente devulve la direccion del nodo que contiene el valor buscado mediante el puntero pasado como tercer argumento.
En caso de que el valor no se encuentre en el arbol, la funcion retorna un "status" de error.

El prototipo para la función es el siguiente.

.. code-block:: c++

    int avl_search(
      float num,
      struct avl_node  **root,
      struct avl_node **found_node);

Para buscar un número, es necesario un puntero a la raíz y el número que se desee buscar y un puntero donde guardar la posicion del nodo encontrado, como en el siguiente ejemplo.

.. code-block:: c++

    int status=AVL_SUCCESS; // Initialize status
    int list_size=3; // Define list size
    float list[3]={1,2,3}; // Create list

    struct avl_node *root=nullptr; // Initially empty root
    status=avl_create(list,list_size,&root); // Create tree

    avl_node *found_node = nullptr; //Create a pointer to save the result position
    status=avl_search(2.0,&root,&found_node); // Look for the element

    free_tree_mem(root); //Free memory assigned to node


4. Pruebas
----------
Esta sección corresponde a una descripción de cada una de las pruebas realizadas.

4.1. Create
~~~~~~~~~~~
Para la creación del árbol sí se cuenta con ambos tipos de pruebas (negativas, positivas), esto debido a que esta creación puede fallar por la inadecuada especificación del tamaño de la lista de entrada para la creación del árbol.

En síntesis se tienen los siguientes casos:

* **Positiva:** Se prueba la creación del árbol con un tamaño de lista correcto, debe devolver AVL_SUCCESS.
* **Negativa:** Se prueba la creación del árbol con un tamaño de lista 0, debe devolver AVL_INVALID_PARAM.

4.2. Insert
~~~~~~~~~~~
Para la inserción de un elemento al árbol, se cuenta con solo pruebas positivas de manera directa, y con pruebas negativas de manera indirecta. Esto debido a que el algoritmo de inserción completo nunca va a generar errores, sin embargo, en las rotaciones de balanceo, si puede fallar.

En síntesis se tienen los siguientes casos:

* **Positiva:** Se prueba la inserción de varios elementos a partir de un nodo raíz vacío, debe devolver AVL_SUCCESS.
* **Rotación izquierda negativa:** Se prueba una rotación hacia la izquierda de una raíz con solamente un hijo izquierdo, debe devolver AVL_INVALID_ROT.
* **Rotación derecha negativa:** Se prueba una rotación hacia la derecha de una raíz con solamente un hijo derecho, debe devolver AVL_INVALID_ROT.

4.3. Delete
~~~~~~~~~~~
Para la eliminación de un número, el algorimto requiere que un árbol previamente creado y tener el número almacenado en él.

En síntesis se tienen los siguientes casos:

* **Positiva:** Se prueba la eliminación de un nodo almacenado en un árbol válido, debe devolver AVL_SUCCESS.
* **Negativa:** Se prueba la eliminación de un nodo en un árbol vacío, debe devolver AVL_NOT_FOUND.
* **Negativa:** Se prueba la eliminación de un nodo no almancenado en el árbol mayor que cualquier valor, debe devolver AVL_OUT_OF_RANGE.
* **Negativa:** Se prueba la eliminación de un nodo no almancenado en el árbol menor que cualquier valor, debe devolver AVL_OUT_OF_RANGE.

4.4. Print
~~~~~~~~~~
Para la comprobación de la correcta impresión de la información, se redirige el *stdout* hacia un buffer y este string se compara con un string de referencia para comprobar así la correcta impresión del árbol.
En esta prueba en particular solo existe una prueba positiva debido a que no hay manera de imprimir incorrectamente el árbol dada una raíz válida, de igual manera el único parámetro que es la raíz (una dirección de memoria) no se puede comprobar como una dirección inválida para el árbol.

De esta manera el test tiene un único caso:

* **Positiva:** Se prueba que la impresión redirigida al buffer sea la misma que la esperada para una lista ya conocida.

4.5. Minimum Element
~~~~~~~~~~~~~~~~~~~~
Para la obtención del elemento mínimo del árbol, se cuenta con una prueba positiva, para cuando se haya un valor, y una prueba negativa cuando el árbol analizado está vacío.

En síntesis se tienen los siguientes casos:

* **Positiva:** Se prueba la obtención de un nodo mínimo en un árbol con N cantidad de valores, debe devolver AVL_SUCCESS.
* **Negativa:** Se prueba la obtención de un nodo mínimo en un árbol vacío, debe devolver AVL_OUT_OF_RANGE.

4.6. Minimum Element
~~~~~~~~~~~~~~~~~~~~
Para la obtención del elemento máximo del árbol, se cuenta con una prueba positiva, para cuando se haya un valor, y una prueba negativa cuando el árbol analizado está vacío.

En síntesis se tienen los siguientes casos:

* **Positiva:** Se prueba la obtención de un nodo máximo en un árbol con N cantidad de valores, debe devolver AVL_SUCCESS.
* **Negativa:** Se prueba la obtención de un nodo máximo en un árbol vacío, debe devolver AVL_OUT_OF_RANGE.

4.7. Search
~~~~~~~~~~~
Para la busqueda de un número, el algorimto requiere que un árbol previamente creado y tener el número almacenado en él.

En síntesis se tienen los siguientes casos:

* **Positiva:** Se prueba la busqueda de un nodo almacenado en un árbol válido, debe devolver AVL_SUCCESS.
* **Negativa:** Se prueba la busqueda de un nodo no almancenado en el árbol mayor que todos los valores, debe devolver AVL_OUT_OF_RANGE.
* **Negativa:** Se prueba la busqueda de un nodo no almancenado en el árbol menor que todos los valores, debe devolver AVL_OUT_OF_RANGE.
* **Negativa:** Se prueba la busqueda de un nodo en un árbol vacío, debe devolver AVL_NOT_FOUND.

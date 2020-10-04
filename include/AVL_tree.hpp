#ifndef AVL_TREE_H
#define AVL_TREE_H
/**
 * Códigos de error
 */
enum avl_error_codes {
  AVL_SUCCESS       = 0,
  AVL_INVALID_PARAM = -1,
  AVL_OUT_OF_RANGE  = -2,
  AVL_TIMEOUT       = -3,
  AVL_NOT_FOUND     = -4,
  AVL_INVALID_ROT   = -5
};

/**
 * Struct que define un nodo de la estructura de datos
 */
struct avl_node {
  /** Puntero al nodo hijo izquierdo */
  struct avl_node *lc_node;

  /** Puntero al nodo hijo derecho */
  struct avl_node *rc_node;

  /** Número flotante asociado al nodo */
  float value;
};


/**
 * max
 * Toma un par de códigos de error y devuelve el menor entre ellos.
 * Retorna el menor código de error.
 *
 * @param [in]  height_1 Altura del nodo desde primera perpectiva (derecho/izquierdo).
 * @param [in]  height_2 Altura del nodo desde segunda perpectiva (derecho/izquierdo).
 *
 * @returns max_height   Máxima altura entre ambas perspectivas.
 *                             
 */
int max(
  int height_1,
  int height_2);


/**
 * min
 * Toma un par de códigos de error y devuelve el menor entre ellos.
 * Retorna el menor código de error.
 *
 * @param [in]  status_1  Error code 1.
 * @param [in]  status_2  Error code 2.
 *
 * @returns error_code    El menor código de error.
 */
int min(
  int status_1,
  int status_2);

/**
 * min3
 * Toma tres códigos de error y devuelve el menor entre ellos.
 * Retorna el menor código de error.
 *
 * @param [in]  status_1  Error code 1.
 * @param [in]  status_2  Error code 2.
 * @param [in]  status_3  Error code 3.
 *
 * @returns error_code    El menor código de error.
 */
int min3(
  int status_1,
  int status_2,
  int status_3);

/**
 * get_height
 * Calcula la altura de un nodo.
 * Retorna la altura del nodo.
 *
 * @param [in]  current_node  Puntero al nodo.
 *
 * @returns height Altura del nodo.
 */
int get_height(
  struct avl_node *current_node);

/**
 * get_balance
 * Calcula el factor de balance de un nodo h(LeftChild)-h(RightChild).
 * Retorna el factor de balance del nodo.
 *
 * @param [in]  current_node  Puntero al nodo.
 *
 * @returns balance_factor Factor de balance.
 */
int get_balance(
  struct avl_node *current_node);

/**
 * new_node
 * Crea un nuevo nodo con el valor indicado.
 * Retorna un puntero al nodo creado.
 *
 * @param [in]  value  Valor para el nodo.
 *
 * @returns node_ptr Puntero al nodo creado.
 */
int new_node(
  struct avl_node **node_ptr,
  float value);


/**
 * left_rotation
 * Realiza una rotación a la izquierda sobre el nodo dado.
 * Retorna el código de error.
 *
 * @param [in/out]  rot_top_node  Puntero doble al nodo root de la rotación.
 *
 * @returns error_code Código de error indicando el éxito o error de la función.
 */
int left_rotation(
  struct avl_node **rot_top_node);

/**
 * left_rotation
 * Realiza una rotación a la derecha sobre el nodo dado.
 * Retorna el código de error.
 *
 * @param [in/out]  rot_top_node  Puntero doble al nodo root de la rotación.
 *
 * @returns error_code Código de error indicando el éxito o error de la función.
 */
int right_rotation(
  struct avl_node **rot_top_node);

/**
 * random_list
 * Crea una lista con números aleatorios del tamaño dado.
 * Retorna un puntero a la lista.
 *
 * @param [in] list_size  Tamaño de la lista deseada.
 *
 * @returns list_ptr Puntero a la lista creada.
 */
float *random_list(
  int list_size
);

/**
 * free_tree_mem
 * Libera la memoria asignada a cada nodo del arbol.
 *
 * @param [in] root_node  Puntero a la raíz del árbol.
 *
 */
void free_tree_mem(
  struct avl_node *root_node);

/**
 * avl_create
 * Toma una lista de números flotantes, y crea la estructura de datos deseada.
 * Retorna el nodo raíz del árbol.
 *
 * @param [in]  in_number_list Lista de números flotantes de entrada.
 * @param [out] new_root_node  Puntero al nodo raíz del árbol creado.
 *
 * @returns error_code Código de error indicando el éxito o error de la función.
 *                             
 */
int avl_create(
  float           *in_number_list,
  int              list_size,
  struct avl_node **new_root_node);


/**
 * avl_node_add
 * Toma un nodo y lo inserta en la estructura de datos.
 * Una nueva raíz puede ser obtenida.
 *
 * @param [in]  num       Número por insertar
 * @param [out] new_root  es el puntero al nuevo nodo raíz del árbol
 *
 * @returns error_code    un código de error indicando el éxito o error
 *                        de la función
 */
int avl_node_add(
  float num,
  struct avl_node **new_root);


/**
 * avl_node_remove
 * Toma un nodo arbitrario, lo busca y lo elimina de la estructura de datos.
 * Da error si el nodo no pertenece al árbol.
 *
 * @param [in]  num            Número por eleminar
 * @param [out] new_root       es el puntero al nuevo nodo raíz del árbol
 *
 * @returns error_code         un código de error indicando el éxito o error
 *                             de la función
 */
int avl_node_remove(
  float num,
  struct avl_node **new_root);


/**
 * avl_search
 * Toma un número flotante, lo busca y se devuelve el nodo al que pertenece.
 * Si existieran varios nodos con el mismo valor, se devuelve cualquiera.
 * Da error si el valor no existe en ningún nodo.
 *
 * @param [in]  in_root        es el nodo raíz original del árbol
 * @param [in]  num            es el número flotante por buscar
 * @param [out] found_node     es el nodo encontrado que contiene el valor
 *
 * @returns error_code         un código de error indicando el éxito o error
 *                             de la función
 */
int avl_search(
  struct avl_node  in_root,
  float                      num,
  struct avl_node *found_node);


/**
 * avl_max_get
 * Se obtiene el nodo que contenga el valor máximo en todo el árbol.
 *
 * @param [in]  in_root   es el nodo raíz original del árbol
 * @param [out] max_node  es el nodo encontrado que contiene el valor máximo
 *
 * @returns error_code    un código de error indicando el éxito o error
 *                        de la función
 */
int avl_max_get(
  struct avl_node  in_root,
  struct avl_node *max_node);


/**
 * avl_min_get
 * Se obtiene el nodo que contenga el valor mínimo en todo el árbol.
 *
 * @param [in]  in_root   es el nodo raíz original del árbol
 * @param [out] min_node  es el nodo encontrado que contiene el valor mínimo
 *
 * @returns error_code    un código de error indicando el éxito o error
 *                        de la función
 */
int avl_min_get(
  struct avl_node *in_root,
  struct avl_node **min_node);


/**
 * avl_print
 * Se imprime el árbol en terminal.
 *
 * @param [in]  in_root   es el nodo raíz original del árbol
 *
 * @returns error_code    un código de error indicando el éxito o error
 *                        de la función
 */
int avl_print(
  struct avl_node  *in_root);


#endif /* AVL_TREE_H */

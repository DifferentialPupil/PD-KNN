#include "m_pd.h"
#include <stdarg.h>
#include "list.c"
 
static t_class *KNN_class;  
 
typedef struct _KNN {  
  t_object x_obj;
  struct Node *head;
  int k;
  int size;
} t_KNN;

void test(t_KNN *x, t_symbol *s, int argc, t_atom *argv) {
  const int size = x->size;
  double points[size];
  for (int i = 0; i < argc; i++) {
    t_atom a = argv[i];
    if (a.a_type != A_FLOAT) {
      post("Non float argument encountered. Point cannot be mapped.");
      return ;
    }
    points[i] = (double)atom_getfloatarg(i, argc, argv);
  }
  outlet_float(x->x_obj.ob_outlet, KNN(x->head, x->k, size, points));
}

void add(t_KNN *x, t_symbol *s, int argc, t_atom *argv)
{
  const int size = x->size;
  double *points = (double *)malloc(size * sizeof(double));
  const int CLASS_ID = atom_getfloatarg(0, argc, argv);
  for (int i = 1; i < argc; i++) {
    t_atom a = argv[i];
    if (a.a_type != A_FLOAT) {
      post("Non float argument encountered. No point was added.");
      return ;
    }
    points[i-1] = (double)atom_getfloatarg(i, argc, argv);
  }
  add_node(points, CLASS_ID, &x->head);
}
 
void *KNN_new(t_floatarg k, t_floatarg size)  
{  
  t_KNN *x = (t_KNN *)pd_new(KNN_class);
  x->k = k;
  x->size = size;
  x->head = NULL;
  outlet_new(&x->x_obj, &s_float);
  return (void *)x;  
}
 
void KNN_setup(void) {  
  KNN_class = class_new(gensym("KNN"),  
    (t_newmethod)KNN_new, NULL,
    sizeof(t_KNN), CLASS_DEFAULT, A_FLOAT, A_FLOAT, 0);  
  class_addmethod(KNN_class, (t_method)add, gensym("add"), A_GIMME, 0);
  class_addmethod(KNN_class, (t_method)test, gensym("test"), A_GIMME, 0);
}

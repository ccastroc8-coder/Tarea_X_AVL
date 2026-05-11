#include <iostream>                         
using namespace std;

//Carlos Daniel Castro Caceres
// ==========================
// ESTRUCTURA STUDENT
// ==========================

struct Student {

    int student_id;
    string full_name;
    string career;
    int semester;
    float gpa;
    int skill_score;

};

// ==========================
// NODO AVL
// ==========================

struct Node {

    Student data;
    Node* left;
    Node* right;
    int height;

};

// ==========================
// CLASE AVL
// ==========================

class AVL {

private:

    Node* root;
    int totalNodes;

    int max(int a, int b) {

        if(a > b) {
            return a;
        }

        return b;
    }

    int getHeight(Node* node) {

        if(node == NULL) {
            return 0;
        }

        return node->height;
    }

    int getBalance(Node* node) {

        if(node == NULL) {
            return 0;
        }

        return getHeight(node->left) - getHeight(node->right);
    }

    Node* rotateRight(Node* y) {

        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(getHeight(y->left),
                        getHeight(y->right)) + 1;

        x->height = max(getHeight(x->left),
                        getHeight(x->right)) + 1;

        return x;
    }

    Node* rotateLeft(Node* x) {

        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(getHeight(x->left),
                        getHeight(x->right)) + 1;

        y->height = max(getHeight(y->left),
                        getHeight(y->right)) + 1;

        return y;
    }

    Node* insert(Node* node, Student student) {

        if(node == NULL) {

            Node* newNode = new Node();

            newNode->data = student;
            newNode->left = NULL;
            newNode->right = NULL;
            newNode->height = 1;

            totalNodes++;

            return newNode;
        }

        // Ordenar por skill_score
        // BONUS: desempate por student_id

        if(student.skill_score < node->data.skill_score) {

            node->left = insert(node->left, student);

        } else if(student.skill_score > node->data.skill_score) {

            node->right = insert(node->right, student);

        } else {

            if(student.student_id < node->data.student_id) {

                node->left = insert(node->left, student);

            } else {

                node->right = insert(node->right, student);
            }
        }

        node->height = 1 + max(getHeight(node->left),
                               getHeight(node->right));

        int balance = getBalance(node);

        // Left Left

        if(balance > 1 &&
           student.skill_score < node->left->data.skill_score) {

            return rotateRight(node);
        }

        // Right Right

        if(balance < -1 &&
           student.skill_score > node->right->data.skill_score) {

            return rotateLeft(node);
        }

        // Left Right

        if(balance > 1 &&
           student.skill_score > node->left->data.skill_score) {

            node->left = rotateLeft(node->left);

            return rotateRight(node);
        }

        // Right Left

        if(balance < -1 &&
           student.skill_score < node->right->data.skill_score) {

            node->right = rotateRight(node->right);

            return rotateLeft(node);
        }

        return node;
    }

    void inorder(Node* node, int &count) {

        if(node != NULL) {

            inorder(node->right, count);

            count++;

            cout << count << ". "
                 << node->data.full_name
                 << " - Score: "
                 << node->data.skill_score
                 << endl;

            inorder(node->left, count);
        }
    }

    Node* search(Node* node, int score) {

        if(node == NULL ||
           node->data.skill_score == score) {

            return node;
        }

        if(score < node->data.skill_score) {

            return search(node->left, score);
        }

        return search(node->right, score);
    }

public:

    AVL() {

        root = NULL;
        totalNodes = 0;
    }

    void insertStudent(Student student) {

        root = insert(root, student);

        cout << "\nEstudiante insertado correctamente.\n";
    }

    void showRanking() {

        if(root == NULL) {

            cout << "\nNo hay estudiantes registrados.\n";

            return;
        }

        int count = 0;

        cout << "\n===== RANKING ACADEMICO =====\n";

        inorder(root, count);
    }

    void searchStudent(int score) {

        Node* result = search(root, score);

        if(result == NULL) {

            cout << "\nEstudiante no encontrado.\n";

        } else {

            cout << "\n===== ESTUDIANTE ENCONTRADO =====\n";

            cout << "ID: "
                 << result->data.student_id
                 << endl;

            cout << "Nombre: "
                 << result->data.full_name
                 << endl;

            cout << "Carrera: "
                 << result->data.career
                 << endl;

            cout << "Semestre: "
                 << result->data.semester
                 << endl;

            cout << "GPA: "
                 << result->data.gpa
                 << endl;

            cout << "Skill Score: "
                 << result->data.skill_score
                 << endl;
        }
    }

    void showStatistics() {

        cout << "\n===== ESTADISTICAS AVL =====\n";

        cout << "Altura actual del arbol: "
             << getHeight(root)
             << endl;

        cout << "Factor de balance de la raiz: "
             << getBalance(root)
             << endl;

        cout << "Cantidad de nodos insertados: "
             << totalNodes
             << endl;
    }
};

// ==========================
// MAIN
// ==========================

int main() {

    AVL tree;

    int option;

    do {

        cout << "\n===== MENU AVL =====\n";

        cout << "1. Insertar estudiante\n";
        cout << "2. Mostrar ranking academico\n";
        cout << "3. Buscar por skill_score\n";
        cout << "4. Mostrar estadisticas AVL\n";
        cout << "5. Salir\n";

        cout << "Ingrese una opcion: ";
        cin >> option;

        switch(option) {

            case 1: {

                Student s;

                cout << "\nIngrese ID: ";
                cin >> s.student_id;

                cin.ignore();

                cout << "Ingrese nombre completo: ";
                getline(cin, s.full_name);

                cout << "Ingrese carrera: ";
                getline(cin, s.career);

                cout << "Ingrese semestre: ";
                cin >> s.semester;

                cout << "Ingrese GPA: ";
                cin >> s.gpa;

                cout << "Ingrese skill score: ";
                cin >> s.skill_score;

                tree.insertStudent(s);

                break;
            }

            case 2: {

                tree.showRanking();

                break;
            }

            case 3: {

                int score;

                cout << "\nIngrese el score a buscar: ";
                cin >> score;

                tree.searchStudent(score);

                break;
            }

            case 4: {

                tree.showStatistics();

                break;
            }

            case 5: {

                cout << "\nSaliendo del programa...\n";

                break;
            }

            default: {

                cout << "\nOpcion invalida.\n";
            }
        }

    } while(option != 5);

    return 0;
}
enum Color {BLACK, RED};

class Node{
    private:
        int value;
        Node *right, *left, *parent;
        Color color;

    public:
        Node(int VALUE);
        ~Node();

        bool has_left();
        bool has_right();
        bool has_two_children();
        bool is_leaf();

        // Getters and Setters
        int get_value();
        Node* get_parent();
        Node* get_right();
        Node* get_left();
        Color get_color();
        Node* get_uncle();
        Node* get_sibling();

        void set_value(int);
        void set_parent(Node*);
        void set_right(Node*);
        void set_left(Node*);
        void set_color(Color);
};
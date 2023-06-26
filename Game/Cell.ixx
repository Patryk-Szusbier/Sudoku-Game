export module Cell;

export class Cell 
{
    private:
        int value;
        bool editable;

    public:
        Cell(int value = 0, bool editable = true) {
            this->value = value;
            this->editable = editable;
        }

        int getValue() const {
            return value;
        }

        void setValue(int value) {
            this->value = value;
        }

        bool isEditable() const {
            return editable;
        }

        void setEditable(bool editable) {
            this->editable = editable;
        }
};
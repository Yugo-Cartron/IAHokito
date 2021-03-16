
static const bool BLACK = false;
static const bool WHITE = true;
class Case 
{
    private :
        
        bool couleur;
        int valeur;
        int pile;

    public :
        Case() {
            this->couleur = BLACK;
            this->valeur = 1;
        }
        Case(const bool c, const int v){
            this->couleur = c;
            this->valeur = v;
        }
        inline bool getCouleur() const {return this->couleur;}
        inline int getValeur() const {return this->valeur;}
        inline int getPile() const {return this->pile;}
        inline void setCouleur(const bool c) { this->couleur = c;}
        inline void setValeur(const int v) { this->valeur = v;}
        inline void setPile(const int p) { this->pile =p;}
        inline bool isPile() const {return this->pile != 1;}
};
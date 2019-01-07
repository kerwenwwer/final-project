enum ObjTypeID
{PLAYER,BULLENT,BACKGROUNG,EMEMY,COMET};

class GameObj{
    public:
        int x;
        int y;
        ObjTypeID ID;

        GameObj(ObjTypeID objTypeID){
            x = 0;
            y = 0;
            this->ID = ID;
        }
};
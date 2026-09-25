#include<iostream>
using namespace std;
#include"raylib.h"

int main(){
    const int Width = 800;
    const int Height = 600;               //Defining
    const int cellsize = 20;
    const int rows = Height/cellsize;
    const int colms = Width/cellsize;
    

    struct Cell{
        public:
        bool alive;
        bool nextalive;                  // Defining stuff for cells
    };

    Cell grid[rows][colms] = {};

    
    
    InitWindow( Width, Height, "Conway's Game Of Life");
    SetTargetFPS(10);

    auto countneighbours = [&](int x, int y) {
      const int offsets[8][2]{
        {-1,  0}, { 1,  0}, { 0, -1}, { 0,  1},
        {-1, -1}, {-1,  1}, { 1, -1}, { 1, 1}
      };

      int count = 0;

      for (int k = 0; k < 8; k++) {                      //Detecting Neighbouring Cells
        int neighbourx = x + offsets[k][0];              //Using std Offsets(As Function)
        int neighboury = y + offsets[k][1];              // Basically the distance between a already present cell ( int x, int y) and the 8 surrounding cells which have the distance wrt the present cell
                                                          
        if (neighbourx >= 0 && neighbourx < rows &&
          neighboury >= 0 && neighboury < colms &&
          grid[neighbourx][neighboury].alive) {
          count++;
        }
      }

      return count;
    };

    grid[2][2].alive = true;
    grid[2][3].alive = true;              //Sample Cells
    grid[3][2].alive = true;
    

    while( WindowShouldClose() == false){
        

        BeginDrawing();
        ClearBackground(BLACK);

        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            int mousecolm = GetMouseX()/cellsize;                           
            int mouserow = GetMouseY()/cellsize;

            if (mouserow >= 0 && mouserow < rows && mousecolm >=0 && mousecolm < colms){
                grid[mouserow][mousecolm].alive = true;                                             // User Can Input 3 Alive Cells Using Mouse Left Key
            }

            if (mouserow + 1 < rows && mousecolm + 1 < colms){
            grid[mouserow ][mousecolm + 1].alive = true;
            grid[mouserow ][mousecolm - 1].alive = true;
            grid[mouserow - 1][mousecolm ].alive = true;
        }
        }

        

        for ( int i = 0 ; i<rows ; i++){
            for( int j = 0; j < colms ;j++){
                int x =j*cellsize;
                int y = i*cellsize;

                int countN = countneighbours( i, j);                     // Calling the Offsets function


                if ( grid[i][j].alive){
                    grid[i][j].nextalive = (countN == 2 || countN == 3);            //First - To Detect the Next Generation using the Output from Neighbouting Cells
                }else{               
                    grid[i][j].nextalive = (countN == 3);
                }

                if (grid[i][j].alive){
                    DrawRectangle(x,y, cellsize, cellsize, WHITE);              //To Draw Already Alive Cells
                }

                
            }

        }
        
            for ( int i = 0 ; i<rows; i++){
                    for ( int j = 0 ; j<colms; j++){                      //To Make Birth of Next Generation
                        grid[i][j].alive = grid[i][j].nextalive;
                    }
            }

        

        EndDrawing();                        /*WITH FLOW OF TIME:_
                                                1.)Some Sample Cells are Active (or from the User)
                                                2.)Now Using the Data from the Neighbouring Cells -- The Next Generation of cells is initialised
                                                3.)Now to Actually draw the current generation on the grid
                                                4.)Finally passing on the family lineage (Nextalive cells will be lit up in the next iteration of the Loop)
                                            */
    }

    CloseWindow();

 return 0;
}


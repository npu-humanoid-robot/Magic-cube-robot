//  Copyright:NPU Soccer Robot Base Humanoid group
//  Author:Zhang Duo
//  Date:2019.2.18
//  Version:2.0
//  This code is using the dfs methods to serach the solution tree.
//  When the rotating surface is F or B, 
//  the number of solution spaces will be bifurcated.
//  In this version,we considered to bifurcate when the rotating surface is U or R



#include <transform.h>
using namespace std;


//U1F2D1B2F1R1D2
//D' R2 L  D  B  U2 F  R2 D' F2 U2 R2 L  F2 B2 R  D2 R' D2 R' B2
//This is the main procedure of deep search.
//The most of functions called are implemented in transform.cpp

void Transform::roationOfLD(int i) {
    i *= 2;
    try
    {
        if(in[i] == 'L') 
        {
        
            if(in[i+1] == '\'')
                leftRCounterwiseAndReturn();
            else if(in[i+1] == '1')
                leftRColckwisAndReturn();
            else if(in[i+1] == '2')
                leftR180();
            else
            {
                throw "the operand is illegal";
            }
        }
        else if(in[i] == 'D')
        {
           
            if(in[i+1] == '\'')
                rightRCounterwiseAndReturn();
            else if(in[i+1] == '1')
                rightRColckwisAndReturn();
            else if(in[i+1] == '2')
                rightR180();
            else
            {
  
                throw "the angel of rotation is illegal";
            }
                    
        }
        else
        {
            throw "the surface to be rotatied is illegal";
        }
        
    }
    catch(const char* msg)
    {
        std::cerr <<msg<<std::endl;
    }

}

void Transform::dfs(int depth) {
    if(depth >= this->maxSearchStep)
    {
        //cout <<"here"<<endl;
        calulateCost();
        //cout <<"here"<<endl;
        //cout <<"cost: "<<cost<<endl;
        if(cost < this->minCost)
        {
            cout <<"update_here"<<endl;
            minCost = cost;
            for(int i = 0;i < this->maxSearchStep;i++)
                finalChoice[i] = choice[i];
            for(int i = 0;i < numAction;i++)
                finalOut[i] = out[i]; 
            finalOut[numAction] = '\0';
        }
    }    
    else
    {
        int i = depth * 2;
        if(in[i] == 'L' || in[i] == 'D')
        {
            int iniActionNum = numAction; //用于保存现场
            choice[depth] = 0;
            roationOfLD(depth);
         
            dfs(depth+1);
            numAction = iniActionNum; //恢复现场
        }
        else if(in[i] == 'R')
        {
            std::string in_tmp = in;//因为要三叉，所以保存现场
            int iniActionNum = numAction; //用于保存现场
            RtoL();
            choice[depth] = 0;
            roationOfLD(depth);
           
            dfs(depth+1);
            numAction = iniActionNum; //用于恢复现场

            /*for(int k = depth * 2;k < in.length();k++)
                in[k] = in_tmp[k];                    //恢复序列现场
            //std::cout <<"R:?"<<in[i]<<std::endl;
            RtoF();
            //std::cout <<"F:?"<<in[i]<<std::endl;
            choice[depth] = 1;
        
            dfs(depth);
            //std::cout <<"F"<<" ";
            numAction = iniActionNum;

            for(int k = depth * 2;k < in.length();k++)
                in[k] = in_tmp[k];                    //恢复序列现场
            //std::cout <<"R:?"<<in[i]<<std::endl;
            RtoB();
            //std::cout <<"B:?"<<in[i]<<std::endl;
            choice[depth] = 2;
            
            dfs(depth);
            numAction = iniActionNum;*/
        }
        else if(in[i] == 'F')
        {
            std::string in_tmp = in; //因为要二叉，所以要保存序列现场
            //两个选择
            int iniActionNum = numAction; //保存动作现场
           
            FtoD();
          
            choice[depth] = 0;
            
            roationOfLD(depth);
            dfs(depth+1);
            numAction = iniActionNum; //恢复动作现场


            for(int i = depth * 2;i < in.length();i++)
                in[i] = in_tmp[i];                    //恢复序列现场
            FtoL();

            choice[depth] = 1;
            roationOfLD(depth);
            dfs(depth+1);
            numAction = iniActionNum;  //恢复动作现场
        
        }
        else if(in[i] == 'U') 
        {
            std::string in_tmp = in;//因为要三叉，所以保存现场
            int iniActionNum = numAction;
            UtoD();
            choice[depth] = 0;
            roationOfLD(depth);
            dfs(depth+1);
            numAction = iniActionNum;

            /*for(int k = depth * 2;k < in.length();k++)
                in[k] = in_tmp[k];                    //恢复序列现场
            //std::cout <<"U:?"<<in[i]<<std::endl;
            UtoF();
            //std::cout <<"F:?"<<in[i]<<std::endl;
            choice[depth] = 1;
            dfs(depth);
            
            numAction = iniActionNum;

            for(int k = depth * 2;k < in.length();k++)
                in[k] = in_tmp[k];
            //std::cout <<"U:?"<<in[i]<<std::endl;                    //恢复序列现场
            UtoB();
            //std::cout <<"D:?"<<in[i]<<std::endl;
            choice[depth] = 2;
            dfs(depth);
            
            numAction = iniActionNum;*/

        }
        else if(in[i] == 'B') //结构同F
        {
            //两个选择
            int iniActionNum = numAction;
            std::string in_tmp = in;
            BtoD();
            choice[depth] = 0;
            roationOfLD(depth);
            
            dfs(depth+1);
            numAction = iniActionNum;
            
            for(int k = depth * 2;k < in.length();k++)
                in[k] = in_tmp[k];

            BtoL();
            choice[depth] = 1;
            roationOfLD(depth);
            dfs(depth+1);
            numAction = iniActionNum;
        }

    }
    
}


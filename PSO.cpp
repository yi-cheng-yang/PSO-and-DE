#include "common.cpp"

#ifndef PSO
    #define PSO

    typedef struct Solution{
        d2d Position;
        d1d ObjectiveValue;
        d2d PersonalBESTPosition;
        d1d PersonalBESTValue;
        d2d Velocity;
    }PARTICLE;

    class PSO_ALGORITHM{
        public:
            d1d run_result;
            d1d eva_result;
            int Max_NFE;

        public:
            void exe(int run, int num_eva, int dim, int pop, int func){
                Max_NFE = num_eva;
                run_result.resize(run, 0.0);
                eva_result.resize(num_eva / pop, 0.0);
                for(int i = 0; i < run; ++i){
                    Construct_SWARM(dim, func, pop);
                    init(dim, func);
                    while(NFE < Max_NFE){
                        Update_Position(dim, func);
                    }
                    run_result[i] = GBESTValue;
                    cout << GBESTValue << endl;
                }
            }
        
        private:
            int NFE;
            double w = 0.729;
            double c1 = 1.49445;
            double c2 = 1.49445;
            PARTICLE SWARM;
            double Vmax;
            double Vmin;

            double BoundMax;
            double BoundMin;

            d1d GBESTPosition;
            double GBESTValue;
            

        private:
            void Construct_SWARM(int dim, int func, int pop){

                NFE = 0;

                // Set function Range 

                SWARM.Position.clear();
                SWARM.ObjectiveValue.clear();
                SWARM.PersonalBESTPosition.clear();
                SWARM.PersonalBESTValue.clear();
                SWARM.Velocity.clear();
                
                SWARM.Position.resize(pop, d1d(dim, 0.0));
                SWARM.ObjectiveValue.resize(pop, DBL_MAX);
                SWARM.PersonalBESTPosition.resize(pop, d1d(dim, 0.0));
                SWARM.PersonalBESTValue.resize(pop, DBL_MAX);
                SWARM.Velocity.resize(pop, d1d(dim, 0.0));


                Vmax = BoundMax;
                Vmin = BoundMin;

                GBESTPosition.clear();
                GBESTPosition.resize(dim, 0.0);

                GBESTValue = DBL_MAX;

            }
            void init(int dim, int func){
                for(int i = 0; i < static_cast<int>(SWARM.Position.size()); ++i){
                    for(int j = 0; j < dim; ++j){
                        SWARM.Position[i][j] = Rdouble(0.0, 1.0) * (BoundMax - BoundMin) + BoundMin;
                        SWARM.Velocity[i][j] = Rdouble(0.0, 1.0) * (Vmax - Vmin) + Vmin;
                    }
                    evaluation(SWARM.Position[i], SWARM.ObjectiveValue[i], dim, func);
                    SWARM.PersonalBESTPosition[i] = SWARM.Position[i];
                    SWARM.PersonalBESTValue[i] = SWARM.ObjectiveValue[i];
                    if(SWARM.ObjectiveValue[i] < GBESTValue){
                        GBESTValue = SWARM.ObjectiveValue[i];
                        GBESTPosition = SWARM.Position[i];
                    }
                }
                eva_result[NFE / static_cast<int>(SWARM.Position.size()) - 1] += GBESTValue; 
            }
            void evaluation(d1d &position, double &value, int dim, int func){
                if(NFE < Max_NFE){
                    
                    //write your objective function
                    ++NFE;
                }
            }
            void Update_Position(int dim, int func){
                for(int i = 0; i < static_cast<int>(SWARM.Position.size()); ++i){
                    for(int j = 0; j < dim; ++j){
                        double temp = w * SWARM.Velocity[i][j] + c1 * Rdouble(0.0, 1.0) * (SWARM.PersonalBESTPosition[i][j] - SWARM.Position[i][j]) + c2 * Rdouble(0.0, 1.0) * (GBESTPosition[j] - SWARM.Position[i][j]);
                        if(temp > Vmax || temp < Vmin){
                            temp = (Vmax - Vmin) * Rdouble(0.0, 1.0) + Vmin;
                        }
                        SWARM.Velocity[i][j] = temp;

                        SWARM.Position[i][j] += SWARM.Velocity[i][j];

                        if(SWARM.Position[i][j] > BoundMax || SWARM.Position[i][j] < BoundMin){
                            SWARM.Position[i][j] = (BoundMax - BoundMin) * Rdouble(0.0, 1.0) + BoundMin;
                        }

                    }
                }

                for(int i = 0; i < static_cast<int>(SWARM.ObjectiveValue.size()); ++i){
                    evaluation(SWARM.Position[i], SWARM.ObjectiveValue[i], dim, func);
                    if(SWARM.ObjectiveValue[i] < SWARM.PersonalBESTValue[i]){
                        SWARM.PersonalBESTValue[i] = SWARM.ObjectiveValue[i];
                        SWARM.PersonalBESTPosition[i] = SWARM.Position[i];
                    }
                    if(SWARM.ObjectiveValue[i] < GBESTValue){
                        GBESTValue = SWARM.ObjectiveValue[i];
                        GBESTPosition = SWARM.Position[i];
                    }
                }

                eva_result[NFE / static_cast<int>(SWARM.Position.size()) - 1] += GBESTValue; 
            }
            
    };

#endif
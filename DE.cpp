#include "common.cpp"


#ifndef DE
    #define DE
    
    class DE_ALGORITHM{
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
                    Construct_Solution(dim, func, pop);
                    init(dim, func);
                    while(NFE < Max_NFE){
                        Mutation_Crossover(dim, func, pop);
                    }
                    run_result[i] = GBESTValue;
                    cout << GBESTValue << endl;
                }
            }

        private:
            int NFE;
            d2d solution;
            d1d objective;
            double F = 0.5;
            double CR = 0.9;

            d1d GBESTPosition;
            double GBESTValue;

            double max, min;

        private:
            void Construct_Solution(int dim, int func, int pop){
                // Set function Range
                NFE = 0;

                solution.clear();
                objective.clear();
                solution.resize(pop, d1d(dim, 0.0));
                objective.resize(pop, DBL_MAX);

                GBESTValue = DBL_MAX;
                GBESTPosition.clear();
                GBESTPosition.resize(dim, 0.0);

            }
            void init(int dim, int func){
                for(int i = 0; i < static_cast<int>(solution.size()); ++i){
                    for(int j = 0; j < dim; ++j){
                        solution[i][j] = Rdouble(0.0, 1.0) * (max - min) + min;
                    }
                    evaluation(solution[i], objective[i], dim, func);
                    if(objective[i] < GBESTValue){
                        GBESTValue = objective[i];
                        GBESTPosition = solution[i];

                    }
                }

                eva_result[NFE / static_cast<int>(solution.size()) - 1] += GBESTValue;
            }

            void evaluation(d1d &position, double &value, int dim, int func){
                if(NFE < Max_NFE){
                    //write your objective function
                    ++NFE;
                }
            }
            void Mutation_Crossover(int dim, int func, int pop){
                d2d temp(pop, d1d(dim , 0.0));
                for(int i = 0; i < pop; ++i){
                    int Rand_dim = Rint(0, dim - 1);
                    int r1, r2, r3;
                    do{
                        r1 = Rint(0, pop - 1);
                    }while(r1 == i);

                    do{
                        r2 = Rint(0, pop - 1);
                    }while(r2 == i || r2 == r1);

                    do{
                        r3 = Rint(0, pop - 1);
                    }while(r3 == i || r3 == r1 || r3 == r2);
                    for(int j = 0; j < dim; ++j){
                        if(Rdouble(0.0, 1.0) < CR || j == Rand_dim){
                            temp[i][j] = solution[r1][j] + F * (solution[r2][j] - solution[r3][j]);
                            if(temp[i][j] > max || temp[i][j] < min){
                                temp[i][j] = (max - min) * Rdouble(0.0, 1.0) + min;
                            }
                        }
                        else{
                            temp[i][j] = solution[i][j];
                        }
                    }
                }

                for(int i = 0; i < pop; ++i){
                    double t_value = DBL_MAX;
                    evaluation(temp[i], t_value, dim, func);
                    if(t_value < objective[i]){
                        solution[i] = temp[i];
                        objective[i] = t_value;
                        if(t_value < GBESTValue){
                            GBESTValue = t_value;
                            GBESTPosition = temp[i];
                        }
                    }
                }
                eva_result[NFE / pop - 1] += GBESTValue;
            }
    };

#endif
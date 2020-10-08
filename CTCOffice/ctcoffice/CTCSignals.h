//ADD GUARD
#ifndef CTCSIGNALS_H
#define CTCSIGNALS_H

#include <iostream>
#include <vector>


class CTCSignals
{
        private:
                void setFlag(bool);
        public:
                bool update_flag = 0;
                int dest_block;
                std::vector<float> ctc_spd;
                std::vector<float> ctc_auth;
                //DELETE DECLARATION
                //PASTE IN DEFINITION
                void setSignal(int b, const std::vector<float> &s, const std::vector<float> &a) {
                        dest_block = b;
                }

};

//END GUARD
#endif

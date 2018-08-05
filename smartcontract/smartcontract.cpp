#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>
using namespace std;
using namespace eosio;

class notechain : public eosio::contract {

	private:
		int32_t userid[10];
		string username[10];
		int32_t token[10];
		int32_t photoid[10];
		string photo[10];
		int32_t animalid[10];
		string animal[10];
		int32_t photonum;
		int32_t animalnum;
		bool verified[10];
		int32_t endangerrate[10];

	public:
		using contract::contract;

		/*
		* Upload the photos to EOS node for verification.
		*/
		string* photoupload (int32_t i, string str[]) 
		{
			string* photoaddress = new string[10];
				while (i > 0){
					photoaddress[i] = str[i];
					i--;
				}
			return photoaddress;
		}

		/*
		* The photo is verified by AI system. EOS appliation gets the verification result of endangered level.
		*/
		void verification  (int32_t i, int32_t rate) {
			endangerrate[i] = rate;
			verified[i] = true;
		}

		/*
		* Get the list of animals from the application.
		*/
		string* animallist (int32_t i) {
			string* photolist = new string[10];
			while (i > 0) {
				photolist[i] = photo[i];
				i--;
			}
			return photolist;
		}

		/*
		* Award token to the person who uploads the animal photos.
		* The number of token awarded depends on the endangered level verified.
		* Endangered level 1 (00% - 30%): Award 10 tokens
		* Endangered level 2 (30% - 60%): Award 20 tokens
		* Endangered level 3 (60% - 90%): Award 50 tokens
		* Endangered level 4 (90% above): Award 100 tokens
		*/
		void awardtoken (account_name to, int32_t tokenCnt) {

			INLINE_ACTION_SENDER(eosio::token, transfer)(N(eosio.token), {_this_contract, N(active)},
														{_this_contract, to, asset(tokenCnt), "user reward"});

			if(endangerrate[i] > 90){
				token[i] = token[i] + 100;
			} else {
					if(endangerrate[i] > 60){
 					 token[i] = token[i] + 50;
					} else
						{
							if(endangerrate[i] > 30){
								token[i] = token[i] + 20;
					} else
					{
						token[i] = token[i] + 10;
					}
				}
			}
		}
};

EOSIO_ABI( notechain, (awardtoken)(verification));
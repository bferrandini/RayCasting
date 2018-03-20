#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>

bool check_map(std::vector<std::string> const& carte)
{
	int lettre_x = 0;

	for (int i = 0; i < carte.size(); ++i)
	{
		for (int j = 0; j < carte[0].size(); ++j)
		{
			if(carte[i][j] == 'X')
				lettre_x++;

			if (carte[i][j] != 'X' && \
				carte[i][j] != '1' && \
				carte[i][j] != '0')
			{
				std::cout << "Il y à un '" << carte[i][j] << "' dans la map... " << std::endl;
				std::cout << "ligne : " << i+1 << " !" << std::endl;
				std::cout << "caractère : " << j+1 << " !" << std::endl;
				return false;
			}
		}
	}

	if(lettre_x == 0)
	{
		std::cout << "Il dois y avoir au minimum 1 'X' dans la map." << std::endl;
		return false;
	}

	if(lettre_x >= 2)
	{
		std::cout << "Il ne dois pas y avoir plus de 1 'X' dans la map." << std::endl;
		return false;
	}

	for (unsigned int i = 0; i < carte.size(); ++i)
	{
		if(i >= 1)
		{
			if(carte[i].size() != carte[i-1].size())
			{
				std::cout << "La map n'est pas rectangulaire." << std::endl;					
				return false;
			}
		}
	}

	unsigned int taille;
	taille = carte.back().size();

	for (unsigned int i = 0; i < taille; ++i)
	{
		if(carte.back()[i] != '1')
		{
			std::cout << "Il y a un trou au su de la map." << std::endl;
			return false;
		}

		if(carte[0][i] != '1')
		{
			std::cout << "Il y a un trou au nord de la map." << std::endl;
			return false;
		}
	}

	for (unsigned int i = 0; i < carte.size(); ++i)
	{
		if(carte[i][0] != '1') // Si le premier charactère de la première ligne est différent de 1...
		{
			std::cout << "Il manque un mur à l'ouest de la carte." << std::endl;
			std::cout <<"ligne numéro : "<< i + 1 << "." << std::endl;
			return false;
		}

		if(carte[i][carte[i].size()-1] != '1')
		{
			std::cout << "Il manque un mur à l'est de la carte." << std::endl;
			std::cout <<"ligne numéro : "<< i + 1 << "." << std::endl;
			return false;
		} 
	}

	std::cout << "Aucune erreur trouvé." << std::endl;
	return true;
}

int main(int argc, char** argv)
{
	std::vector <std::string> lignes;
	std::string ligne;
	std::ifstream map("../map.rc");
	
	while(getline(map, ligne))
		lignes.push_back(ligne);

	std::cout << check_map(lignes) << std::endl;

	return 0;
}
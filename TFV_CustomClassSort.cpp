#include "TFV_Classes.h"

		// The short snippet below was created by David Krauss (Potatoswatter)
		// and can be located in the address below:
		// https://stackoverflow.com/questions/5635909/c-how-to-sort-vectorclass-with-operator
		// As it is from stackexchange, the snippet (and consequently the rest of this entire project not covered by any other license) is licensed under CC-BY-SA 4.0.
		// a copy of the license can be found below:
		// https://creativecommons.org/licenses/by-sa/4.0/legalcode
		// Some modifications were made

bool item_less( item lhs, item rhs ) {
    return lhs.GetPriority().GetPriorityIndex() < rhs.GetPriority().GetPriorityIndex();
}

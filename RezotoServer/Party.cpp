#include "Party.h"
#include <cstdlib>
#include <ctime>

Party::Party() : m_score(0)
{
	m_ID = rand();
}

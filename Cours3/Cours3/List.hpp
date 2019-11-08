#pragma once

template<typename Type>

class List
{
public:
	Type elem;

	List<Type>* next = nullptr;

	List(const Type & elem) {
		this->elem = elem;
	};

	int Length()
	{
		if (nullptr == next) return 1;
		else return next->Length()+1;
	}

	//ajoute elem à la fin de la liste
	void Append(const Type & elem) {

		if (next == nullptr) next = new List(elem);
		else next->Append(elem);
	}

	//ajoute elem au début de la liste
	List<Type >* addFirst(const Type & elem) {

		auto lolo = new List(elem);	
		
		lolo->next = this;
		return lolo;

	}

	List<Type>* Remove(const Type & removeme) {

		if (this->elem == removeme)
		{
			auto suite = next;						
			this->next = nullptr;
			delete this;
			if (suite != nullptr)
			{
				return suite->Remove(removeme);
				
			}
			else
			{
				return nullptr;
			}
		}
		else {
			if (next)
				next = next->Remove(removeme);
			return this;

		}
	}

	void Contains(const Type & elemATrouver) {
		if (elem == elemATrouver)
			return true;
		else if (next == nullptr)
			return false;
		else
			return next->Contains(elemATrouver);

	}
};

typedef List<int> IntList;
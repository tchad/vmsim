#include <string>
#include <vector>
#include <type_traits>

#ifndef VM_H_
#define VM_H_

#include "Constant.h"
#include "BackingStore.h"
#include "MM.h"
#include "PageTable.h"

class VM final {
public:
	class Result;
	static Result simulate(const std::string &addresses);
	static STATUS handlePageFault(BackingStore &bs, MM &mm, PageTable &pt, PAGENUM pagenum, FRAMENUM &framenum);

	class Result final {
	public:
		struct Itm {
			VADDR vAddr;
			PADDR pAddr;
			byte value;
		};
		using RESULTDATA = std::vector<Itm>;
		using size_type = RESULTDATA::size_type;

		Result() = default;
		Result(const Result&) = delete;
		Result& operator=(const Result&) = delete;

		Result(Result &&r);
		Result& operator=(Result &&r);

		size_type count() const;
		const RESULTDATA* data() const;
		const Itm item(size_type i) const;
		STATUS status() const;


	private:
		RESULTDATA _data;
		STATUS _status = FAILED;

		void append(Itm itm);
		void setStatus(STATUS status);
		friend class VM;
	};

	VM() = delete;
};


inline const VM::Result::Itm VM::Result::item(VM::Result::size_type i) const
{
	return _data[i];
}

#endif /* VM_H_ */

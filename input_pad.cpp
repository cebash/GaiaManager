
#include "input_pad.h"
#include <cell/pad/libpad.h>
//#include <cell/pad/error.h>
#define CELL_OK 0 // include cell pad error.h didn't works, and was just neede by this

InputPad * InputPad::instance = 0;

int InputPad::init(void)
{
    return cellPadInit(1);
}

InputPad* InputPad::getSingle( void)
{
    if( instance == 0)
        instance = new InputPad();
    return instance;
}

void InputPad::free( void)
{
    delete instance;
    instance = 0;

	cellPadEnd();
}

InputPad::InputPad()
{
    old_info = 0;
    new_pad = 0;
    old_pad = 0;
}


int InputPad::read(void)
{
	int ret;

	u32 padd;

	CellPadData databuf;
#if (CELL_SDK_VERSION<=0x210001)
	CellPadInfo infobuf;
#else
	CellPadInfo2 infobuf;
#endif


#if (CELL_SDK_VERSION<=0x210001)
	ret = cellPadGetInfo(&infobuf);
#else
	ret = cellPadGetInfo2(&infobuf);
#endif
	if (ret != 0) {
		old_pad = new_pad = 0;
		return 1;
	}
#if (CELL_SDK_VERSION<=0x210001)
	if (infobuf.status[0] == CELL_PAD_STATUS_DISCONNECTED) {
#else
	if (infobuf.port_status[0] == CELL_PAD_STATUS_DISCONNECTED) {
#endif
		old_pad = new_pad = 0;
		return 1;
	}
#if (CELL_SDK_VERSION<=0x210001)
	if ((infobuf.info & CELL_PAD_INFO_INTERCEPTED)
		&& (!(old_info & CELL_PAD_INFO_INTERCEPTED))) {
		old_info = infobuf.info;
	} else if ((!(infobuf.info & CELL_PAD_INFO_INTERCEPTED))
			   && (old_info & CELL_PAD_INFO_INTERCEPTED)) {
		old_info = infobuf.info;
		old_pad = new_pad = 0;
		return 1;
	}
#else
	if ((infobuf.system_info & CELL_PAD_INFO_INTERCEPTED)
		&& (!(old_info & CELL_PAD_INFO_INTERCEPTED))) {
		old_info = infobuf.system_info;
	} else if ((!(infobuf.system_info & CELL_PAD_INFO_INTERCEPTED))
			   && (old_info & CELL_PAD_INFO_INTERCEPTED)) {
		old_info = infobuf.system_info;
		old_pad = new_pad = 0;
		return 1;
	}
#endif

	ret = cellPadGetData(0, &databuf);

	if (ret != CELL_OK) {
		old_pad = new_pad = 0;
		return 1;
	}

	if (databuf.len == 0) {
		new_pad = 0;
		return 1;
	}

	padd = (databuf.button[2] | (databuf.button[3] << 8));

	new_pad = padd & (~old_pad);
	old_pad = padd;

	return 1;
}

/* vim: set ts=4 sw=4 sts=4 tw=120 */


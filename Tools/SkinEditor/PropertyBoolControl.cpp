/*!
	@file
	@author		Albert Semenov
	@date		08/2010
*/
#include "precompiled.h"
#include "PropertyBoolControl.h"

namespace tools
{

	PropertyBoolControl::PropertyBoolControl(MyGUI::Widget* _parent) :
		wraps::BaseLayout("PropertyBoolControl.layout", _parent),
		mComboBox(nullptr)
	{
		assignWidget(mComboBox, "ComboBox");

		mComboBox->addItem("True");
		mComboBox->addItem("False");

		mComboBox->eventComboChangePosition += MyGUI::newDelegate(this, &PropertyBoolControl::notifyComboChangePosition);
	}

	PropertyBoolControl::~PropertyBoolControl()
	{
		mComboBox->eventComboChangePosition -= MyGUI::newDelegate(this, &PropertyBoolControl::notifyComboChangePosition);
	}

	void PropertyBoolControl::updateProperty()
	{
		Property* prop = getProperty();
		if (prop != nullptr)
		{
			mComboBox->setEnabled(true);
			size_t index = getComboIndex(prop->getValue());
			mComboBox->setIndexSelected(index);
		}
		else
		{
			mComboBox->setIndexSelected(MyGUI::ITEM_NONE);
			mComboBox->setEnabled(false);
		}
	}

	void PropertyBoolControl::notifyComboChangePosition(MyGUI::ComboBox* _sender, size_t _index)
	{
		Property* prop = getProperty();
		if (prop != nullptr)
		{
			if (_index != MyGUI::ITEM_NONE)
				prop->setValue(mComboBox->getItemNameAt(_index), getTypeName());
			else
				prop->setValue("", getTypeName());
		}
	}

	size_t PropertyBoolControl::getComboIndex(const MyGUI::UString& _name)
	{
		size_t result = MyGUI::ITEM_NONE;

		size_t count = mComboBox->getItemCount();
		for (size_t index=0; index<count; ++index)
		{
			if (mComboBox->getItemNameAt(index) == _name)
			{
				result = index;
				break;
			}
		}

		return result;
	}

} // namespace tools
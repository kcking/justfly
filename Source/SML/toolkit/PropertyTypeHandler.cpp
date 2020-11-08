﻿#include "PropertyTypeHandler.h"

const FName PC_Exec(TEXT("exec"));
const FName PC_Boolean(TEXT("bool"));
const FName PC_Byte(TEXT("byte"));
const FName PC_Class(TEXT("class"));
const FName PC_Int(TEXT("int"));
const FName PC_Int64(TEXT("int64"));
const FName PC_Float(TEXT("float"));
const FName PC_Name(TEXT("name"));
const FName PC_Delegate(TEXT("delegate"));
const FName PC_MCDelegate(TEXT("mcdelegate"));
const FName PC_Object(TEXT("object"));
const FName PC_Interface(TEXT("interface"));
const FName PC_String(TEXT("string"));
const FName PC_Text(TEXT("text"));
const FName PC_Struct(TEXT("struct"));
const FName PC_Wildcard(TEXT("wildcard"));
const FName PC_Enum(TEXT("enum"));
const FName PC_SoftObject(TEXT("softobject"));
const FName PC_SoftClass(TEXT("softclass"));
const FName PSC_Self(TEXT("self"));
const FName PSC_Index(TEXT("index"));
const FName PSC_Bitmask(TEXT("bitmask"));
const FName PN_Execute(TEXT("execute"));

FEdGraphPinType FPropertyTypeHelper::DeserializeGraphPinType(const TSharedRef<FJsonObject>& PinJson) {
	FEdGraphPinType GraphPinType;
	GraphPinType.PinCategory = *PinJson->GetStringField(TEXT("PinCategory"));
	GraphPinType.PinSubCategory = *PinJson->GetStringField(TEXT("PinSubCategory"));
	if (PinJson->HasField(TEXT("PinSubCategoryObject"))) {
		const FString& ObjectPath = PinJson->GetStringField(TEXT("PinSubCategoryObject"));
		UObject* PinSubCategoryObject = LoadObject<UObject>(NULL, *ObjectPath);
		check(PinSubCategoryObject != nullptr);
		GraphPinType.PinSubCategoryObject = PinSubCategoryObject;
	}
	if (PinJson->HasField(TEXT("PinSubCategoryMemberReference"))) {
		FSimpleMemberReference& MemberRef = GraphPinType.PinSubCategoryMemberReference;
		const TSharedPtr<FJsonObject>& MemberJson = PinJson->GetObjectField(TEXT("PinSubCategoryMemberReference"));
		if (MemberJson->HasField("MemberParent")) {
			const FString& ObjectPath = MemberJson->GetStringField(TEXT("MemberParent"));
			UObject* MemberParentObject = LoadObject<UObject>(NULL, *ObjectPath);
			check(MemberParentObject != nullptr);
			MemberRef.MemberParent = MemberParentObject;
		}
		MemberRef.MemberName = *MemberJson->GetStringField(TEXT("MemberName"));
		FGuid::Parse(MemberJson->GetStringField(TEXT("MemberGuid")), MemberRef.MemberGuid);
	}

	if (PinJson->HasField(TEXT("PinValueType"))) {
		FEdGraphTerminalType& ValueType = GraphPinType.PinValueType;
		const TSharedPtr<FJsonObject> ValueJson = PinJson->GetObjectField(TEXT("PinValueType"));
		ValueType.TerminalCategory = *ValueJson->GetStringField(TEXT("TerminalCategory"));
		ValueType.TerminalSubCategory = *ValueJson->GetStringField(TEXT("TerminalSubCategory"));
		if (ValueJson->HasField(TEXT("TerminalSubCategoryObject"))) {
			const FString& ObjectPath = ValueJson->GetStringField(TEXT("TerminalSubCategoryObject"));
			UObject* TerminalSubCategoryObject = LoadObject<UObject>(NULL, *ObjectPath);
			check(TerminalSubCategoryObject != nullptr);
			ValueType.TerminalSubCategoryObject = TerminalSubCategoryObject;
		}
		ValueType.bTerminalIsConst = ValueJson->GetBoolField(TEXT("TerminalIsConst"));
		ValueType.bTerminalIsWeakPointer = ValueJson->GetBoolField(TEXT("TerminalIsWeakPointer"));
	}

	if (PinJson->HasField(TEXT("ContainerType"))) {
		GraphPinType.ContainerType = static_cast<EPinContainerType>(PinJson->GetIntegerField(TEXT("ContainerType")));
	}
	if (PinJson->HasField(TEXT("IsReference"))) {
		GraphPinType.bIsReference = PinJson->GetBoolField(TEXT("IsReference"));
	}
	if (PinJson->HasField(TEXT("IsConst"))) {
		GraphPinType.bIsConst = PinJson->GetBoolField(TEXT("IsConst"));
	}
	if (PinJson->HasField(TEXT("IsWeakPointer"))) {
		GraphPinType.bIsWeakPointer = PinJson->GetBoolField(TEXT("IsWeakPointer"));
	}
	return GraphPinType;
}

TSharedRef<FJsonObject> FPropertyTypeHelper::SerializeGraphPinType(const FEdGraphPinType& GraphPinType) {
	TSharedRef<FJsonObject> TypeEntry = MakeShareable(new FJsonObject());
	TypeEntry->SetStringField(TEXT("PinCategory"), GraphPinType.PinCategory.ToString());
	TypeEntry->SetStringField(TEXT("PinSubCategory"), GraphPinType.PinCategory.ToString());

	UObject* subCategoryObject = GraphPinType.PinSubCategoryObject.Get();
	if (subCategoryObject != nullptr) {
		TypeEntry->SetStringField(TEXT("PinSubCategoryObject"), subCategoryObject->GetPathName());
	}

	const FSimpleMemberReference& memberRef = GraphPinType.PinSubCategoryMemberReference;
	if (memberRef.MemberGuid.IsValid()) {
		TSharedRef<FJsonObject> memberReference = MakeShareable(new FJsonObject());
		if (memberRef.MemberParent != nullptr) {
			memberReference->SetStringField(TEXT("MemberParent"), memberRef.MemberParent->GetPathName());
		}
		memberReference->SetStringField(TEXT("MemberName"), memberRef.MemberName.ToString());
		memberReference->SetStringField(TEXT("MemberGuid"), memberRef.MemberGuid.ToString());
		TypeEntry->SetObjectField(TEXT("PinSubCategoryMemberReference"), memberReference);
	}
	
	if (GraphPinType.ContainerType == EPinContainerType::Map) {
		TSharedRef<FJsonObject> pinValueType = MakeShareable(new FJsonObject());
		pinValueType->SetStringField(TEXT("TerminalCategory"), GraphPinType.PinValueType.TerminalCategory.ToString());
		pinValueType->SetStringField(TEXT("TerminalSubCategory"), GraphPinType.PinValueType.TerminalSubCategory.ToString());
		UObject* terminalSubCategoryObject = GraphPinType.PinValueType.TerminalSubCategoryObject.Get();
		if (terminalSubCategoryObject != nullptr) {
			pinValueType->SetStringField(TEXT("TerminalSubCategoryObject"), terminalSubCategoryObject->GetPathName());
		}
		pinValueType->SetBoolField(TEXT("TerminalIsConst"), GraphPinType.PinValueType.bTerminalIsConst);
		pinValueType->SetBoolField(TEXT("TerminalIsWeakPointer"), GraphPinType.PinValueType.bTerminalIsWeakPointer);
		TypeEntry->SetObjectField(TEXT("PinValueType"), pinValueType);
	}

	if (GraphPinType.ContainerType != EPinContainerType::None) {
		TypeEntry->SetNumberField(TEXT("ContainerType"), static_cast<uint8>(GraphPinType.ContainerType));
	}
	if (GraphPinType.bIsReference) {
		TypeEntry->SetBoolField(TEXT("IsReference"), GraphPinType.bIsReference);
	}
	if (GraphPinType.bIsConst) {
		TypeEntry->SetBoolField(TEXT("IsConst"), GraphPinType.bIsConst);
	}
	if (GraphPinType.bIsWeakPointer) {
		TypeEntry->SetBoolField(TEXT("IsWeakPointer"), GraphPinType.bIsWeakPointer);
	}
	return TypeEntry;
}

bool GetPropertyCategoryInfo(const UProperty* TestProperty, FName& OutCategory, FName& OutSubCategory, UObject*& OutSubCategoryObject, bool& bOutIsWeakPointer);

bool FPropertyTypeHelper::ConvertPropertyToPinType(const UProperty* Property, /*out*/ FEdGraphPinType& TypeOut) {
	if (Property == nullptr) {
		TypeOut.PinCategory = TEXT("bad_type");
		return false;
	}

	TypeOut.PinSubCategory = NAME_None;

	// Handle whether or not this is an array property
	const UMapProperty* MapProperty = Cast<const UMapProperty>(Property);
	const USetProperty* SetProperty = Cast<const USetProperty>(Property);
	const UArrayProperty* ArrayProperty = Cast<const UArrayProperty>(Property);
	const UProperty* TestProperty = Property;
	if (MapProperty) {
		TestProperty = MapProperty->KeyProp;

		// set up value property:
		UObject* SubCategoryObject = nullptr;
		bool bIsWeakPtr = false;
		bool bResult = GetPropertyCategoryInfo(MapProperty->ValueProp, TypeOut.PinValueType.TerminalCategory, TypeOut.PinValueType.TerminalSubCategory, SubCategoryObject, bIsWeakPtr);
		TypeOut.PinValueType.TerminalSubCategoryObject = SubCategoryObject;

		if (bIsWeakPtr) {
			return false;
		}

		if (!bResult) {
			return false;
		}
	} else if (SetProperty) {
		TestProperty = SetProperty->ElementProp;
	} else if (ArrayProperty) {
		TestProperty = ArrayProperty->Inner;
	}
	TypeOut.ContainerType = FEdGraphPinType::ToPinContainerType(ArrayProperty != nullptr, SetProperty != nullptr, MapProperty != nullptr);
	TypeOut.bIsReference = Property->HasAllPropertyFlags(CPF_OutParm | CPF_ReferenceParm);
	TypeOut.bIsConst = Property->HasAllPropertyFlags(CPF_ConstParm);

	// Check to see if this is the wildcard property for the target container type
	if (const UMulticastDelegateProperty* MulticastDelegateProperty = Cast<const UMulticastDelegateProperty>(TestProperty)) {
		TypeOut.PinCategory = PC_MCDelegate;
		FMemberReference::FillSimpleMemberReference<UFunction>(MulticastDelegateProperty->SignatureFunction, TypeOut.PinSubCategoryMemberReference);
	} else if (const UDelegateProperty* DelegateProperty = Cast<const UDelegateProperty>(TestProperty)) {
		TypeOut.PinCategory = PC_Delegate;
		FMemberReference::FillSimpleMemberReference<UFunction>(DelegateProperty->SignatureFunction, TypeOut.PinSubCategoryMemberReference);
	} else {
		UObject* SubCategoryObject = nullptr;
		bool bIsWeakPointer = false;
		bool bResult = GetPropertyCategoryInfo(TestProperty, TypeOut.PinCategory, TypeOut.PinSubCategory, SubCategoryObject, bIsWeakPointer);
		TypeOut.bIsWeakPointer = bIsWeakPointer;
		TypeOut.PinSubCategoryObject = SubCategoryObject;
		if (!bResult) {
			return false;
		}
	}
	return true;
}

bool GetPropertyCategoryInfo(const UProperty* TestProperty, FName& OutCategory, FName& OutSubCategory, UObject*& OutSubCategoryObject, bool& bOutIsWeakPointer) {
	if (const UInterfaceProperty* InterfaceProperty = Cast<const UInterfaceProperty>(TestProperty)) {
		OutCategory = PC_Interface;
		OutSubCategoryObject = InterfaceProperty->InterfaceClass;
	} else if (const UClassProperty* ClassProperty = Cast<const UClassProperty>(TestProperty)) {
		OutCategory = PC_Class;
		OutSubCategoryObject = ClassProperty->MetaClass;
	} else if (const USoftClassProperty* SoftClassProperty = Cast<const USoftClassProperty>(TestProperty)) {
		OutCategory = PC_SoftClass;
		OutSubCategoryObject = SoftClassProperty->MetaClass;
	} else if (const USoftObjectProperty* SoftObjectProperty = Cast<const USoftObjectProperty>(TestProperty)) {
		OutCategory = PC_SoftObject;
		OutSubCategoryObject = SoftObjectProperty->PropertyClass;
	} else if (const UObjectPropertyBase* ObjectProperty = Cast<const UObjectPropertyBase>(TestProperty)) {
		OutCategory = PC_Object;
		OutSubCategoryObject = ObjectProperty->PropertyClass;
		bOutIsWeakPointer = TestProperty->IsA(UWeakObjectProperty::StaticClass());
	} else if (const UStructProperty* StructProperty = Cast<const UStructProperty>(TestProperty)) {
		OutCategory = PC_Struct;
		OutSubCategoryObject = StructProperty->Struct;
	} else if (TestProperty->IsA<UFloatProperty>()) {
		OutCategory = PC_Float;
	} else if (TestProperty->IsA<UInt64Property>()) {
		OutCategory = PC_Int64;
	} else if (TestProperty->IsA<UIntProperty>()) {
		OutCategory = PC_Int;
	} else if (const UByteProperty* ByteProperty = Cast<const UByteProperty>(TestProperty)) {
		OutCategory = PC_Byte;
		OutSubCategoryObject = ByteProperty->Enum;
	} else if (const UEnumProperty* EnumProperty = Cast<const UEnumProperty>(TestProperty)) {
		// K2 only supports byte enums right now - any violations should have been caught by UHT or the editor
		if (!EnumProperty->GetUnderlyingProperty()->IsA<UByteProperty>()) {
			OutCategory = TEXT("unsupported_enum_type");
			return false;
		}

		OutCategory = PC_Byte;
		OutSubCategoryObject = EnumProperty->GetEnum();
		
	} else if (TestProperty->IsA<UNameProperty>()) {
		OutCategory = PC_Name;
	} else if (TestProperty->IsA<UBoolProperty>()) {
		OutCategory = PC_Boolean;
	} else if (TestProperty->IsA<UStrProperty>()) {
		OutCategory = PC_String;
	} else if (TestProperty->IsA<UTextProperty>()) {
		OutCategory = PC_Text;
	} else {
		OutCategory = TEXT("bad_type");
		return false;
	}

	return true;
}

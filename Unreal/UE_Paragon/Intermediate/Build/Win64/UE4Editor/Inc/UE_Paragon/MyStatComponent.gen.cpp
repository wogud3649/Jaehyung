// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "UE_Paragon/MyStatComponent.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeMyStatComponent() {}
// Cross Module References
	UE_PARAGON_API UScriptStruct* Z_Construct_UScriptStruct_FCharacterStat();
	UPackage* Z_Construct_UPackage__Script_UE_Paragon();
	ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FTableRowBase();
	UE_PARAGON_API UClass* Z_Construct_UClass_UMyStatComponent_NoRegister();
	UE_PARAGON_API UClass* Z_Construct_UClass_UMyStatComponent();
	ENGINE_API UClass* Z_Construct_UClass_UActorComponent();
// End Cross Module References

static_assert(std::is_polymorphic<FCharacterStat>() == std::is_polymorphic<FTableRowBase>(), "USTRUCT FCharacterStat cannot be polymorphic unless super FTableRowBase is polymorphic");

class UScriptStruct* FCharacterStat::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern UE_PARAGON_API uint32 Get_Z_Construct_UScriptStruct_FCharacterStat_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FCharacterStat, Z_Construct_UPackage__Script_UE_Paragon(), TEXT("CharacterStat"), sizeof(FCharacterStat), Get_Z_Construct_UScriptStruct_FCharacterStat_Hash());
	}
	return Singleton;
}
template<> UE_PARAGON_API UScriptStruct* StaticStruct<FCharacterStat>()
{
	return FCharacterStat::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FCharacterStat(FCharacterStat::StaticStruct, TEXT("/Script/UE_Paragon"), TEXT("CharacterStat"), false, nullptr, nullptr);
static struct FScriptStruct_UE_Paragon_StaticRegisterNativesFCharacterStat
{
	FScriptStruct_UE_Paragon_StaticRegisterNativesFCharacterStat()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("CharacterStat")),new UScriptStruct::TCppStructOps<FCharacterStat>);
	}
} ScriptStruct_UE_Paragon_StaticRegisterNativesFCharacterStat;
	struct Z_Construct_UScriptStruct_FCharacterStat_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_level_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_level;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_maxHp_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_maxHp;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_attack_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_attack;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FCharacterStat_Statics::Struct_MetaDataParams[] = {
		{ "ModuleRelativePath", "MyStatComponent.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FCharacterStat_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FCharacterStat>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FCharacterStat_Statics::NewProp_level_MetaData[] = {
		{ "Category", "CharacterStat" },
		{ "ModuleRelativePath", "MyStatComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FCharacterStat_Statics::NewProp_level = { "level", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FCharacterStat, level), METADATA_PARAMS(Z_Construct_UScriptStruct_FCharacterStat_Statics::NewProp_level_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCharacterStat_Statics::NewProp_level_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FCharacterStat_Statics::NewProp_maxHp_MetaData[] = {
		{ "Category", "CharacterStat" },
		{ "ModuleRelativePath", "MyStatComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FCharacterStat_Statics::NewProp_maxHp = { "maxHp", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FCharacterStat, maxHp), METADATA_PARAMS(Z_Construct_UScriptStruct_FCharacterStat_Statics::NewProp_maxHp_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCharacterStat_Statics::NewProp_maxHp_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FCharacterStat_Statics::NewProp_attack_MetaData[] = {
		{ "Category", "CharacterStat" },
		{ "ModuleRelativePath", "MyStatComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FCharacterStat_Statics::NewProp_attack = { "attack", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FCharacterStat, attack), METADATA_PARAMS(Z_Construct_UScriptStruct_FCharacterStat_Statics::NewProp_attack_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCharacterStat_Statics::NewProp_attack_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FCharacterStat_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCharacterStat_Statics::NewProp_level,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCharacterStat_Statics::NewProp_maxHp,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCharacterStat_Statics::NewProp_attack,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FCharacterStat_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_UE_Paragon,
		Z_Construct_UScriptStruct_FTableRowBase,
		&NewStructOps,
		"CharacterStat",
		sizeof(FCharacterStat),
		alignof(FCharacterStat),
		Z_Construct_UScriptStruct_FCharacterStat_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCharacterStat_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FCharacterStat_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCharacterStat_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FCharacterStat()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FCharacterStat_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_UE_Paragon();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("CharacterStat"), sizeof(FCharacterStat), Get_Z_Construct_UScriptStruct_FCharacterStat_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FCharacterStat_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FCharacterStat_Hash() { return 3601666589U; }
	void UMyStatComponent::StaticRegisterNativesUMyStatComponent()
	{
	}
	UClass* Z_Construct_UClass_UMyStatComponent_NoRegister()
	{
		return UMyStatComponent::StaticClass();
	}
	struct Z_Construct_UClass_UMyStatComponent_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UMyStatComponent_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UActorComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_UE_Paragon,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UMyStatComponent_Statics::Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Custom" },
		{ "IncludePath", "MyStatComponent.h" },
		{ "ModuleRelativePath", "MyStatComponent.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UMyStatComponent_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UMyStatComponent>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UMyStatComponent_Statics::ClassParams = {
		&UMyStatComponent::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x00B000A4u,
		METADATA_PARAMS(Z_Construct_UClass_UMyStatComponent_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UMyStatComponent_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UMyStatComponent()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UMyStatComponent_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UMyStatComponent, 1335454414);
	template<> UE_PARAGON_API UClass* StaticClass<UMyStatComponent>()
	{
		return UMyStatComponent::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UMyStatComponent(Z_Construct_UClass_UMyStatComponent, &UMyStatComponent::StaticClass, TEXT("/Script/UE_Paragon"), TEXT("UMyStatComponent"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UMyStatComponent);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif

// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef UE_PARAGON_MyAnimInstance_generated_h
#error "MyAnimInstance.generated.h already included, missing '#pragma once' in MyAnimInstance.h"
#endif
#define UE_PARAGON_MyAnimInstance_generated_h

#define UE_Paragon_Source_UE_Paragon_MyAnimInstance_h_17_SPARSE_DATA
#define UE_Paragon_Source_UE_Paragon_MyAnimInstance_h_17_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execAnimNotify_AttackHit);


#define UE_Paragon_Source_UE_Paragon_MyAnimInstance_h_17_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execAnimNotify_AttackHit);


#define UE_Paragon_Source_UE_Paragon_MyAnimInstance_h_17_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUMyAnimInstance(); \
	friend struct Z_Construct_UClass_UMyAnimInstance_Statics; \
public: \
	DECLARE_CLASS(UMyAnimInstance, UAnimInstance, COMPILED_IN_FLAGS(0 | CLASS_Transient), CASTCLASS_None, TEXT("/Script/UE_Paragon"), NO_API) \
	DECLARE_SERIALIZER(UMyAnimInstance)


#define UE_Paragon_Source_UE_Paragon_MyAnimInstance_h_17_INCLASS \
private: \
	static void StaticRegisterNativesUMyAnimInstance(); \
	friend struct Z_Construct_UClass_UMyAnimInstance_Statics; \
public: \
	DECLARE_CLASS(UMyAnimInstance, UAnimInstance, COMPILED_IN_FLAGS(0 | CLASS_Transient), CASTCLASS_None, TEXT("/Script/UE_Paragon"), NO_API) \
	DECLARE_SERIALIZER(UMyAnimInstance)


#define UE_Paragon_Source_UE_Paragon_MyAnimInstance_h_17_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UMyAnimInstance(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UMyAnimInstance) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UMyAnimInstance); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UMyAnimInstance); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UMyAnimInstance(UMyAnimInstance&&); \
	NO_API UMyAnimInstance(const UMyAnimInstance&); \
public:


#define UE_Paragon_Source_UE_Paragon_MyAnimInstance_h_17_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UMyAnimInstance(UMyAnimInstance&&); \
	NO_API UMyAnimInstance(const UMyAnimInstance&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UMyAnimInstance); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UMyAnimInstance); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UMyAnimInstance)


#define UE_Paragon_Source_UE_Paragon_MyAnimInstance_h_17_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO___speed() { return STRUCT_OFFSET(UMyAnimInstance, _speed); } \
	FORCEINLINE static uint32 __PPO___isFalling() { return STRUCT_OFFSET(UMyAnimInstance, _isFalling); } \
	FORCEINLINE static uint32 __PPO___vertical() { return STRUCT_OFFSET(UMyAnimInstance, _vertical); } \
	FORCEINLINE static uint32 __PPO___horizontal() { return STRUCT_OFFSET(UMyAnimInstance, _horizontal); } \
	FORCEINLINE static uint32 __PPO___attackMontage() { return STRUCT_OFFSET(UMyAnimInstance, _attackMontage); }


#define UE_Paragon_Source_UE_Paragon_MyAnimInstance_h_14_PROLOG
#define UE_Paragon_Source_UE_Paragon_MyAnimInstance_h_17_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	UE_Paragon_Source_UE_Paragon_MyAnimInstance_h_17_PRIVATE_PROPERTY_OFFSET \
	UE_Paragon_Source_UE_Paragon_MyAnimInstance_h_17_SPARSE_DATA \
	UE_Paragon_Source_UE_Paragon_MyAnimInstance_h_17_RPC_WRAPPERS \
	UE_Paragon_Source_UE_Paragon_MyAnimInstance_h_17_INCLASS \
	UE_Paragon_Source_UE_Paragon_MyAnimInstance_h_17_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define UE_Paragon_Source_UE_Paragon_MyAnimInstance_h_17_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	UE_Paragon_Source_UE_Paragon_MyAnimInstance_h_17_PRIVATE_PROPERTY_OFFSET \
	UE_Paragon_Source_UE_Paragon_MyAnimInstance_h_17_SPARSE_DATA \
	UE_Paragon_Source_UE_Paragon_MyAnimInstance_h_17_RPC_WRAPPERS_NO_PURE_DECLS \
	UE_Paragon_Source_UE_Paragon_MyAnimInstance_h_17_INCLASS_NO_PURE_DECLS \
	UE_Paragon_Source_UE_Paragon_MyAnimInstance_h_17_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> UE_PARAGON_API UClass* StaticClass<class UMyAnimInstance>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID UE_Paragon_Source_UE_Paragon_MyAnimInstance_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS

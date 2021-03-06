#pragma once

#include "SDockTab.h"
#include "JavascriptEditorLibrary.h"
#include "JavascriptEditorTab.generated.h"

UENUM()
namespace EJavascriptTabRole
{
	enum Type
	{
		MajorTab,
		PanelTab,
		NomadTab,
		DocumentTab		
	};
}

class UJavascriptEditorTabManager;
/**
 * 
 */
UCLASS()
class JAVASCRIPTEDITOR_API UJavascriptEditorTab : public UObject, public IEditorExtension
{
	GENERATED_UCLASS_BODY()

public:	
	DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(UWidget*, FSpawnTab, UObject*, Context);
	DECLARE_DYNAMIC_DELEGATE_OneParam(FCloseTab, UWidget*, Widget);

#if WITH_EDITOR
	UPROPERTY()
	FSpawnTab OnSpawnTab;	

	UPROPERTY()
	FCloseTab OnCloseTab;

	UPROPERTY()
	FJavascriptWorkspaceItem Group;

	UPROPERTY(BlueprintReadWrite, Category = "Javascript | Editor")
	FName TabId;

	UPROPERTY(BlueprintReadWrite, Category = "Javascript | Editor")
	FText DisplayName;

	UPROPERTY(BlueprintReadWrite, Category = "Javascript | Editor")
	bool bIsNomad;

	UPROPERTY(BlueprintReadWrite, Category = "Javascript | Editor")
	TEnumAsByte<EJavascriptTabRole::Type> Role;

	UFUNCTION(BlueprintCallable, Category = "Javascript | Editor")
	void Commit();

	UFUNCTION(BlueprintCallable, Category = "Javascript | Editor")
	void Discard();

	UFUNCTION(BlueprintCallable, Category = "Javascript | Editor")
	void CloseTab(UWidget* Widget);

	bool bRegistered;

	UWidget* TakeWidget(UObject* Context);

	virtual void Register() override;
	virtual void Unregister() override;

	virtual void BeginDestroy() override;

	void Register(TSharedRef<FTabManager> TabManager, UObject* Context, TSharedRef<FWorkspaceItem> Group);
	void Unregister(TSharedRef<FTabManager> TabManager);

	static TSharedPtr<SDockTab> MajorTab;
	static TSharedPtr<SDockTab> FindDocktab(UWidget* Widget);
#endif
};

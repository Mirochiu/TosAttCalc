//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TTosAttCalcMainForm : public TForm
{
__published:	// IDE-managed Components
  TBitBtn *Process;
  TLabeledEdit *Att1;
  TLabeledEdit *Att2;
  TLabeledEdit *Att3;
  TLabeledEdit *Att4;
  TLabeledEdit *Att5;
  TLabeledEdit *Att6;
  TMemo *MsgBoard;
  TGroupBox *Setting;
  TLabeledEdit *AttGemNum;
  TLabeledEdit *PowerGemNum;
  TLabeledEdit *ComboNum;
  TLabeledEdit *AttGemChainNum;
  TGroupBox *GroupBox1;
  TGroupBox *GroupBox2;
  TCheckBox *Jinx;
  TLabeledEdit *Rec1;
  TLabeledEdit *Rec2;
  TLabeledEdit *Rec3;
  TLabeledEdit *Rec4;
  TLabeledEdit *Rec5;
  TLabeledEdit *Rec6;
  TLabeledEdit *YourHP;
  TLabeledEdit *YourTotalHP;
  TCheckBox *Odin;
  TLabeledEdit *EnemyNum;
  TCheckBox *Mercenary;
  TLabeledEdit *RecChain;
  TLabeledEdit *EnemyDef;
  TEdit *TeamName;
  TGroupBox *GroupBox3;
  TSpeedButton *Team1;
  TSpeedButton *Team2;
  TSpeedButton *Team3;
  TSpeedButton *Team4;
  TSpeedButton *Team5;
  TSpeedButton *Team6;
  TSpeedButton *Team7;
  TSpeedButton *Team8;
  TSpeedButton *Team9;
  TSpeedButton *Team10;
  TLabeledEdit *AttRate1;
  TLabeledEdit *AttRate2;
  TLabel *Label4;
  TLabel *Label5;
  TCheckBox *TwoTypeLeader;
  TCheckBox *Add2_00;
  TCheckBox *Combo8DoubleAtt;
  TCheckBox *WaterWitch;
  TCheckBox *Add1_50;
  TLabel *Label2;
  TLabel *Label3;
  TLabel *Label1;
  TCheckBox *Undead;
  TCheckBox *GemAdd0_05;
  TCheckBox *LightEgg;
  TCheckBox *AddAttForPowGem;
  TCheckBox *WoodWitch;
  TCheckBox *Dagi1;
  TCheckBox *Dagi2;
  TCheckBox *Wolve;
  TCheckBox *TwoGemMatchLeader;
  void __fastcall ProcessClick(TObject *Sender);
  void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
  void __fastcall TeamSelectClick(TObject *Sender);
  void __fastcall ReturnKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
  void __fastcall Label4Click(TObject *Sender);
  void __fastcall Label5Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
  __fastcall TTosAttCalcMainForm(TComponent* Owner);


  int last_team_idx;
  
  int GetCurrentTeam();

  void LoadCommon();
  void SaveCommon();

  void LoadTeam(int TeamId = -1);
  void SaveTeam(int TeamId = -1);
};
//---------------------------------------------------------------------------
extern PACKAGE TTosAttCalcMainForm *TosAttCalcMainForm;
//---------------------------------------------------------------------------
#endif

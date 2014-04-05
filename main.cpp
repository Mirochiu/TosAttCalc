  //---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <Registry.hpp>

#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TTosAttCalcMainForm *TosAttCalcMainForm;

#define STORE_PATH "Software\\TosAttCalc"

bool SetRegistryValue(AnsiString KeyName, AnsiString Val)
{
  bool saved = false;
  TRegistry *Registry = new TRegistry;
  try
  {
    Registry->RootKey = HKEY_CURRENT_USER;
    if (Registry->OpenKey(STORE_PATH, true))
    {
      Registry->WriteString(KeyName,Val);
      saved = true;
    }
  }
  __finally
  {
    delete Registry;
  }
  return Registry;
}

bool SetRegistryBool(AnsiString KeyName, bool Val)
{
  bool saved = false;
  TRegistry *Registry = new TRegistry;
  try
  {
    Registry->RootKey = HKEY_CURRENT_USER;
    if (Registry->OpenKey(STORE_PATH, true))
    {
      Registry->WriteBool(KeyName,Val);
      saved = true;
    }
  }
  __finally
  {
    delete Registry;
  }
  return Registry;
}


AnsiString GetRegistryValue(AnsiString KeyName, AnsiString def_val, bool AllowEmpty = true)
{
  AnsiString S = def_val;
  TRegistry *Registry = new TRegistry;
  try
  {
    Registry->RootKey = HKEY_CURRENT_USER;
    if (Registry->OpenKey(STORE_PATH, false))
      S = Registry->ReadString(KeyName);

    delete Registry;
  }
  catch(...)
  {
    delete Registry;
    GetRegistryValue(KeyName, def_val);
  }
  if (S.IsEmpty() && !AllowEmpty)
    S = def_val;
  return S;
}

bool GetRegistryBool(AnsiString KeyName, bool def_val)
{
  bool S = def_val;
  TRegistry *Registry = new TRegistry;
  try
  {
    Registry->RootKey = HKEY_CURRENT_USER;
    if (Registry->OpenKey(STORE_PATH, false))
    {
      S = Registry->ReadBool(KeyName);
    }
    delete Registry;
  }
  catch(...)
  {
    SetRegistryBool(KeyName, def_val);
    delete Registry;
  }
  return S;
}


inline double StrToNum(AnsiString str, double def_val)
{
  try
  {
    if (str.IsEmpty())
      return def_val;
    return str.ToDouble();
  }
  catch (...)
  {
    return def_val;
  }
}

int TTosAttCalcMainForm::GetCurrentTeam()
{
  int team_idx = -1;
  
  if (Team1->Down)
    team_idx = 1;
  else if (Team2->Down)
    team_idx = 2;
  else if (Team3->Down)
    team_idx = 3;
  else if (Team4->Down)
    team_idx = 4;
  else if (Team5->Down)
    team_idx = 5;
  else if (Team6->Down)
    team_idx = 6;
  else if (Team7->Down)
    team_idx = 7;
  else if (Team8->Down)
    team_idx = 8;
  else if (Team9->Down)
    team_idx = 9;
  else if (Team10->Down)
    team_idx = 10;

  if (team_idx == -1)
  {
    Team1->Down = true;
    team_idx = 1;
    last_team_idx = 1;
  }

  return team_idx;
}

//---------------------------------------------------------------------------
__fastcall TTosAttCalcMainForm::TTosAttCalcMainForm(TComponent* Owner)
  : TForm(Owner)
{
  this->Caption = this->Caption + " ---- 此版本釋出時間: "  __DATE__ " " __TIME__;

  LoadCommon();
  last_team_idx = 1;  // for save change
  LoadTeam();
}
//---------------------------------------------------------------------------

void TTosAttCalcMainForm::LoadTeam(int TeamId)
{
  if (TeamId<=0) TeamId = GetCurrentTeam();

  AnsiString sTeamPrefix = "Team"+IntToStr(TeamId) + ".";

  TeamName->Text = GetRegistryValue(sTeamPrefix+"Name", "尚未命名的隊伍"+IntToStr(TeamId), false);

  Att1->Text = GetRegistryValue(sTeamPrefix+"Att1", "1651", false);
  Att2->Text = GetRegistryValue(sTeamPrefix+"Att2", "1490", false);
  Att3->Text = GetRegistryValue(sTeamPrefix+"Att3", "1492", false);
  Att4->Text = GetRegistryValue(sTeamPrefix+"Att4", "1314", false);
  Att5->Text = GetRegistryValue(sTeamPrefix+"Att5", "0", false);
  Att6->Text = GetRegistryValue(sTeamPrefix+"Att6", "1651", false);

  AttRate1->Text = GetRegistryValue(sTeamPrefix+"AttRate1", "2.5", false);
  AttRate2->Text = GetRegistryValue(sTeamPrefix+"AttRate2", "2.5", false);

  Rec1->Text = GetRegistryValue(sTeamPrefix+"Rec1", "438", false);
  Rec2->Text = GetRegistryValue(sTeamPrefix+"Rec2", "355", false);
  Rec3->Text = GetRegistryValue(sTeamPrefix+"Rec3", "355", false);
  Rec4->Text = GetRegistryValue(sTeamPrefix+"Rec4", "383", false);
  Rec5->Text = GetRegistryValue(sTeamPrefix+"Rec5", "0", false);
  Rec6->Text = GetRegistryValue(sTeamPrefix+"Rec6", "438", false);

  WoodWitch->Checked = GetRegistryBool(sTeamPrefix+"WoodWitch", true);
  Dagi1->Checked     = GetRegistryBool(sTeamPrefix+"Dagi1", false);
  Dagi2->Checked     = GetRegistryBool(sTeamPrefix+"Dagi2", false);
  AddAttForPowGem->Checked = GetRegistryBool(sTeamPrefix+"AddAttForPowGem", true);

  YourTotalHP->Text  = GetRegistryValue(sTeamPrefix+"TotalHP", "1", false);

  TwoGemLeader->Checked = GetRegistryBool(sTeamPrefix+"TwoGemLeader", false);
}

void TTosAttCalcMainForm::SaveTeam(int TeamId)
{
  if (TeamId<=0) TeamId = GetCurrentTeam();

  AnsiString sTeamPrefix = "Team"+IntToStr(TeamId) + ".";

  SetRegistryValue(sTeamPrefix+"Name", TeamName->Text);
  
  SetRegistryValue(sTeamPrefix+"Att1", Att1->Text);
  SetRegistryValue(sTeamPrefix+"Att2", Att2->Text);
  SetRegistryValue(sTeamPrefix+"Att3", Att3->Text);
  SetRegistryValue(sTeamPrefix+"Att4", Att4->Text);
  SetRegistryValue(sTeamPrefix+"Att5", Att5->Text);
  SetRegistryValue(sTeamPrefix+"Att6", Att6->Text);

  SetRegistryValue(sTeamPrefix+"AttRate1", AttRate1->Text);
  SetRegistryValue(sTeamPrefix+"AttRate2", AttRate2->Text);

  SetRegistryValue(sTeamPrefix+"Rec1", Rec1->Text);
  SetRegistryValue(sTeamPrefix+"Rec2", Rec2->Text);
  SetRegistryValue(sTeamPrefix+"Rec3", Rec3->Text);
  SetRegistryValue(sTeamPrefix+"Rec4", Rec4->Text);
  SetRegistryValue(sTeamPrefix+"Rec5", Rec5->Text);
  SetRegistryValue(sTeamPrefix+"Rec6", Rec6->Text);

  SetRegistryBool(sTeamPrefix+"WoodWitch", WoodWitch->Checked);
  SetRegistryBool(sTeamPrefix+"Dagi1", Dagi1->Checked);
  SetRegistryBool(sTeamPrefix+"Dagi2", Dagi2->Checked);
  SetRegistryBool(sTeamPrefix+"AddAttForPowGem", AddAttForPowGem->Checked);

  SetRegistryValue(sTeamPrefix+"TotalHP", YourTotalHP->Text);

  SetRegistryBool(sTeamPrefix+"TwoGemLeader", TwoGemLeader->Checked);
}

void TTosAttCalcMainForm::LoadCommon()
{
  AttGemNum->Text      = GetRegistryValue("AttGemNum", "3", false);
  PowerGemNum->Text    = GetRegistryValue("PowerGemNum", "");
  AttGemChainNum->Text = GetRegistryValue("AttGemChainNum", "1", false);
  ComboNum->Text       = GetRegistryValue("ComboNum", "5", false);

  EnemyDef->Text = GetRegistryValue("EnemyDef", "120000", false);

  FireWitch->Checked = GetRegistryBool("FireWitch", false);
  Add2_00->Checked   = GetRegistryBool("12StarAdd2_00", false);
  Add1_50->Checked   = GetRegistryBool("DemonAdd1_50", false);
  Jinx->Checked      = GetRegistryBool("Jinx", false);
  DoubleAtt->Checked = GetRegistryBool("12StarDoubleAtt", false);
  Combo8DoubleAtt->Checked = GetRegistryBool("Combo8DoubleAtt", false);
  WaterWitch->Checked = GetRegistryBool("WaterWitch", false);
  Undead->Checked    = GetRegistryBool("Undead", false);
  GemAdd0_05->Checked = GetRegistryBool("GemAdd0_05", false);

  Mercenary->Checked = GetRegistryBool("Mercenary", false);
  RecChain->Text     = GetRegistryValue("RecChainNum", "");

  Odin->Checked      = GetRegistryBool("Odin", false);
  YourHP->Text       = GetRegistryValue("CurrentHP", "1", false);
  
  LightEgg->Checked  = GetRegistryBool("LightEgg", false);
}
//---------------------------------------------------------------------------

void __fastcall TTosAttCalcMainForm::FormClose(TObject *Sender,
      TCloseAction &Action)
{
  bool isOk = true;

  SaveTeam();


  // common
  isOk &=  SetRegistryValue("AttGemNum", AttGemNum->Text);
  isOk &=  SetRegistryValue("PowerGemNum", PowerGemNum->Text);
  isOk &=  SetRegistryValue("AttGemChainNum", AttGemChainNum->Text);
  isOk &=  SetRegistryValue("ComboNum", ComboNum->Text);

  isOk &=  SetRegistryValue("EnemyDef", EnemyDef->Text);

  isOk &=  SetRegistryBool("FireWitch", FireWitch->Checked);
  isOk &=  SetRegistryBool("12StarAdd2_00", Add2_00->Checked);
  isOk &=  SetRegistryBool("DemonAdd1_50", Add1_50->Checked);
  isOk &=  SetRegistryBool("Jinx", Jinx->Checked);
  isOk &=  SetRegistryBool("12StarDoubleAtt", DoubleAtt->Checked);
  isOk &=  SetRegistryBool("Combo8DoubleAtt", Combo8DoubleAtt->Checked);
  isOk &=  SetRegistryBool("WaterWitch", WaterWitch->Checked);
  isOk &=  SetRegistryBool("Undead", Undead->Checked);
  isOk &=  SetRegistryBool("GemAdd0_05", GemAdd0_05->Checked);

  isOk &=  SetRegistryBool("Mercenary", Mercenary->Checked);
  isOk &=  SetRegistryValue("RecChainNum", RecChain->Text);

  isOk &=  SetRegistryBool("Odin", Odin->Checked);
  isOk &=  SetRegistryValue("CurrentHP", YourHP->Text);

  isOk &=  SetRegistryBool("LightEgg", LightEgg->Checked);
  isOk &=  SetRegistryValue("RecChainNum", RecChain->Text);
}
//---------------------------------------------------------------------------

void __fastcall TTosAttCalcMainForm::ProcessClick(TObject *Sender)
{
  int HP, TotalHP;
  HP = StrToNum(YourHP->Text, 1);
  if (HP <=0)
  {
    ShowMessage("奧丁技能需要填寫目前的血量，請填寫你目前的血量 (目前的血量需要大於0)!");
    return;
  }
  YourHP->Text = HP;
  TotalHP = StrToNum(YourTotalHP->Text, 1);
  if (TotalHP<=0)
  {
    ShowMessage("奧丁技能需要填寫總共血量，請填寫你隊伍的總共血量 (目前的總共血量需要大於0)!");
    return;
  }
  YourTotalHP->Text = TotalHP;

  int TotalRecChainNum = 0;
  if (Mercenary->Checked)
  {
    TotalRecChainNum = StrToNum(RecChain->Text,-1);
    if (TotalRecChainNum<0)
    {
      RecChain->Text = "";
      ShowMessage("魔族傭兵的技能需要扣除心珠的Combo數，請填寫心珠串數!");
      return;
    }
    RecChain->Text = TotalRecChainNum;
  }

  int TotalEnemyNum = 1;
  if (LightEgg->Checked)
  {
    TotalEnemyNum = StrToNum(EnemyNum->Text, 0);
    if (TotalEnemyNum<=0)
    {
      EnemyNum->Text = "";
      ShowMessage("光蛋技能需要知道敵人數量，請告訴我敵人的數量是多少??");
      return;
    }
    EnemyNum->Text = TotalEnemyNum;
  }


  MsgBoard->Lines->Clear();

  int Max_Attack = 0;

  int att;
  int EachAtt[6];

  Att1->Text = EachAtt[0] = att = StrToNum(Att1->Text,0);
  Max_Attack = Max_Attack>att?Max_Attack:att;

  Att2->Text = EachAtt[1] = att = StrToNum(Att2->Text,0);
  Max_Attack = Max_Attack>att?Max_Attack:att;

  Att3->Text = EachAtt[2] = att = StrToNum(Att3->Text,0);
  Max_Attack = Max_Attack>att?Max_Attack:att;

  Att4->Text = EachAtt[3] = att = StrToNum(Att4->Text,0);
  Max_Attack = Max_Attack>att?Max_Attack:att;

  Att5->Text = EachAtt[4] = att = StrToNum(Att5->Text,0);
  Max_Attack = Max_Attack>att?Max_Attack:att;

  Att6->Text = EachAtt[5] = att = StrToNum(Att6->Text,0);
  Max_Attack = Max_Attack>att?Max_Attack:att;


  if (WaterWitch->Checked)
  {
    int rec;
    
    Rec1->Text = rec = StrToNum(Rec1->Text,0);
    EachAtt[0] += rec*2.5;
    Max_Attack = EachAtt[0]>Max_Attack?EachAtt[0]:Max_Attack;

    Rec2->Text = rec = StrToNum(Rec2->Text,0);
    EachAtt[1] += rec*2.5;
    Max_Attack = EachAtt[1]>Max_Attack?EachAtt[1]:Max_Attack;

    Rec3->Text = rec = StrToNum(Rec3->Text,0);
    EachAtt[2] += rec*2.5;
    Max_Attack = EachAtt[2]>Max_Attack?EachAtt[2]:Max_Attack;

    Rec4->Text = rec = StrToNum(Rec4->Text,0);
    EachAtt[3] += rec*2.5;
    Max_Attack = EachAtt[3]>Max_Attack?EachAtt[3]:Max_Attack;

    Rec5->Text = rec = StrToNum(Rec5->Text,0);
    EachAtt[4] += rec*2.5;
    Max_Attack = EachAtt[4]>Max_Attack?EachAtt[4]:Max_Attack;

    Rec6->Text = rec = StrToNum(Rec6->Text,0);
    EachAtt[5] += rec*2.5;
    Max_Attack = EachAtt[5]>Max_Attack?EachAtt[5]:Max_Attack;
  }

  int TotalAttack = 0;
  for (int i=0 ; i<6 ; ++i)
    TotalAttack += EachAtt[i];

  MsgBoard->Lines->Add("隊伍總攻擊力=" + FloatToStr(TotalAttack) + " 單張最高攻擊力=" + FloatToStr(Max_Attack));

  //---

  double TotalAttRate = 1;

  double AttRate;

  bool ShowErrorRateMsg = false;

  AttRate = StrToNum(AttRate1->Text,1);
  if (AttRate<=0)
  {
    AttRate = 1.0;
    ShowErrorRateMsg = true;
  }
  AttRate1->Text = AttRate;
  TotalAttRate *= AttRate;

  AttRate = StrToNum(AttRate2->Text,1);
  if (AttRate<=0)
  {
    AttRate = 1.0;
    ShowErrorRateMsg = true;
  }
  AttRate2->Text = AttRate;
  TotalAttRate *= AttRate;

  MsgBoard->Lines->Add("總攻擊倍率=" + FloatToStr(TotalAttRate*100) + "%");

  //---

  bool hasTwoGemLeader = TwoGemLeader->Checked;

  int TotalAttackGem  = StrToNum(AttGemNum->Text,0);
  AttGemNum->Text = TotalAttackGem;

  int TotalAttackPowGem = StrToNum(PowerGemNum->Text,0);
  PowerGemNum->Text = TotalAttackPowGem;

  int AttackGemChainNum = StrToNum(AttGemChainNum->Text,(TotalAttackGem>(hasTwoGemLeader?2:3))?1:0); // auto seting 1 or 0 chain
  AttGemChainNum->Text = AttackGemChainNum;

  int TotalCombo = StrToNum(ComboNum->Text, (TotalAttackGem>(hasTwoGemLeader?2:3))?1:0); // auto seting 1 or 0 combo
  ComboNum->Text = TotalCombo;

  double AdditionalComboRate = 0.0;
  if (Mercenary->Checked)
  {
    AdditionalComboRate = (TotalCombo-AttackGemChainNum-TotalRecChainNum)*0.5;
  }

  int AdditionalGem = TotalAttackGem - (hasTwoGemLeader?2:3)*AttackGemChainNum;
  double AddGemRate = AdditionalGem*0.25;  // 額外消除的攻珠的加乘倍率
  double PowGemRate = TotalAttackPowGem * (AddAttForPowGem->Checked?0.25:0.15); //強珠加成倍率
  double GemRate    = AttackGemChainNum * (hasTwoGemLeader?0.75:1.0) + AdditionalComboRate + AddGemRate + PowGemRate;

  MsgBoard->Lines->Add("總消珠加成="   + FloatToStr(GemRate*100) + "%"
                       " ("  + FloatToStr(AttackGemChainNum*100) + "%"
                       " + " + FloatToStr(AddGemRate*100)        + "%"
                       " + " + FloatToStr(PowGemRate*100)        + "%" ")");
  //MsgBoard->Lines->Add("(攻擊珠加成="   + FloatToStr(AttackGemChainNum*100) + "%");
  //MsgBoard->Lines->Add(" 額外消攻擊珠加成=" + FloatToStr(AddGemRate*100) + "%");
  //MsgBoard->Lines->Add(" 強化攻擊珠加成="   + FloatToStr(PowGemRate*100) + "%"  ")");

  //---

  double EachComboRate = 25;

  if (WoodWitch->Checked)
    EachComboRate += 25;

  if (Dagi1->Checked || Dagi2->Checked)
  {
    EachComboRate += 75;
    
    if (Dagi1->Checked && Dagi2->Checked)
      EachComboRate += 100;
  }

  double TotalComboRate =  1.0 + (TotalCombo-1)*EachComboRate/100.0;

  MsgBoard->Lines->Add("總Combo加成=" + FloatToStr(TotalComboRate*100) + "%"
                       " (每C+" + FloatToStr(EachComboRate) + "%)");

  //---

  double TotalAddAtt = 1;

  if (FireWitch->Checked)
    TotalAddAtt *= 1.5;

  if (Add2_00->Checked)
    TotalAddAtt *= 2;

  if (Add1_50->Checked)
    TotalAddAtt *= 1.5;

  if (Undead->Checked)
  {
    Jinx->Checked = true;
    TotalAddAtt *= 1.5;
  }

  if (Jinx->Checked)
    TotalAddAtt *= 1.5;

  if (DoubleAtt->Checked)
    TotalAddAtt *= 2;

  if (TotalCombo>8 && Combo8DoubleAtt->Checked)
    TotalAddAtt *= 2;

  double OdinAddAtt = 1; 
  if (Odin->Checked)
  {
    OdinAddAtt += 1.5*(1.0-HP/(double)TotalHP);
    TotalAddAtt *= OdinAddAtt;
  }

  if (GemAdd0_05->Checked)
    TotalAddAtt *= 1 + TotalAttackGem * 0.05;

  AnsiString AddAttMsg = "總增傷加成=" + FormatFloat("####0.00",(TotalAddAtt<=1?0:TotalAddAtt)*100) + "%";
  if (Odin->Checked)
  {
    AddAttMsg += "(奧丁增傷=" + FormatFloat("####0.00",OdinAddAtt<=1?0:OdinAddAtt*100) + "%)";
  }
  MsgBoard->Lines->Add(AddAttMsg);

  //---

  double TotalRate = TotalAttRate*GemRate*TotalComboRate*TotalAddAtt;

  int TotalEnemyDef = 0;
  EnemyDef->Text = TotalEnemyDef = StrToNum(EnemyDef->Text, 0);

  int EachDamage[6] = {0};
  int ActDamage[6] = {0};
  for (int i=0 ; i<6 ; ++i)
  {
    if (WoodWitch->Checked && TotalCombo<4)
      ActDamage[i] = EachDamage[i] = 0;
    else
    {
      EachDamage[i] = EachAtt[i]*TotalRate; // 無條件捨去
      ActDamage[i] = EachDamage[i]-TotalEnemyDef<0?1:EachDamage[i]-TotalEnemyDef;
    }

    if (TotalEnemyNum>1)
    {
      // 分散的傷害
      for (int j=0 ; j<6 ; ++j)
        if (i!=j)
        {
          EachDamage[j] += (TotalEnemyNum-1)*(int)(ActDamage[i]/2);
          ActDamage[j]  += (TotalEnemyNum-1)*(int)(ActDamage[i]/2);
        }
    }
  }

  double TotalDamage = 0;
  double ActuralDamage = 0;
  for (int i=0 ; i<6 ; ++i)
  {
    TotalDamage += EachDamage[i];
    ActuralDamage += ActDamage[i];;
    MsgBoard->Lines->Add("卡片" + IntToStr(i+1) + ""
        " 傷害" + FormatFloat("###,###,###,##0", (double)EachDamage[i]) +
        " 扣防後=" + FormatFloat("###,###,###,##0", (double)ActDamage[i]) );
  }
  //MsgBoard->Lines->Add("單張最高傷害=" + FormatFloat("###,###,###,##0", (double)((int)(Max_Attack*TotalRate))));
  MsgBoard->Lines->Add("=========================");
  MsgBoard->Lines->Add("隊伍總傷害="    + FormatFloat("###,###,###,##0", TotalDamage));
  MsgBoard->Lines->Add("扣防後隊伍總傷害=" + FormatFloat("###,###,###,##0", ActuralDamage));


  if (ShowErrorRateMsg)
  {
    ShowMessage("你填入的攻擊倍率不正常,我們自動重設為1, 因為攻擊倍率至少是1!");
  }
}
//---------------------------------------------------------------------------

void __fastcall TTosAttCalcMainForm::TeamSelectClick(TObject *Sender)
{
  int TeamId = GetCurrentTeam();
  if (TeamId != last_team_idx)
  {
    SaveTeam(last_team_idx);
    //ShowMessage("儲存了隊伍" + IntToStr(last_team_idx) + "的設定\r\n"
    //            "載入了隊伍" + IntToStr(TeamId) + "的設定!");
    last_team_idx = TeamId;
    LoadTeam();

    TWinControl* ctrl = dynamic_cast<TWinControl*>(Sender);
    if (ctrl) ctrl->SetFocus();
  }
}
//---------------------------------------------------------------------------

void __fastcall TTosAttCalcMainForm::ReturnKeyDown(TObject *Sender,
      WORD &Key, TShiftState Shift)
{
  if (Key == VK_RETURN) {
    TWinControl* ctrl = FindNextControl(ActiveControl, true, true, false);
    if (ctrl)
      ctrl->SetFocus();
  }
}
//---------------------------------------------------------------------------


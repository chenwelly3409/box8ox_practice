using System;
using System.Web;
using System.Web.UI;
using iTextSharp.text;
using iTextSharp.text.pdf;
using iTextSharp.tool.xml;
using System.IO;
using System.Text;
using System.Collections.Generic;
using System.Linq;
using System.Net;

namespace work
{

	public partial class Default : System.Web.UI.Page
	{
		public void button1Clicked(object sender, EventArgs args)
		{
			
			var doc1 = new Document(PageSize.A4, 50, 50, 80, 50);
			// 設定PageSize及Margin left, right, top, bottom;

			MemoryStream Memory = new MemoryStream();
			PdfWriter PdfWriter = PdfWriter.GetInstance(doc1, Memory);

			/* 
			 string path = Server.MapPath("pdf");
			 PdfWriter PdfWriter = PdfWriter.GetInstance( doc1, new FileStream( path + "/ pdfexample.pdf", FileMode.Create ) );
			 // 如果要在Server端產生pdf
			*/

			BaseFont bfChinese = BaseFont.CreateFont( @"/Users/chenjianzhi/Library/Fonts/kaiu.ttf", BaseFont.IDENTITY_H, BaseFont.NOT_EMBEDDED);
			Font ChFont = new Font(bfChinese, 12);

			Font ChFont_blue = new Font(bfChinese, 40, Font.NORMAL, new BaseColor(51, 0, 153));
			Font ChFont_msg = new Font(bfChinese, 12, Font.ITALIC, BaseColor.RED);

			doc1.Open();
			doc1.Add(new Paragraph("1"));
			doc1.Add(new Paragraph(10f, "▓申請表" , ChFont));
			doc1.Add(new Paragraph("2"));
			doc1.Add(new Paragraph(10f, "Hello FUCK U", ChFont_blue ));
			doc1.Close();

			// 下載
			Response.Clear();
			Response.AddHeader("Content-disposition", "attachment; filename = pdfEX.pdf");
			Response.ContentType = "application/octet-steam";
			Response.OutputStream.Write(Memory.GetBuffer(), 0, Memory.GetBuffer().Length);
			Response.OutputStream.Flush();
			Response.OutputStream.Close();
			Response.Flush();
			Response.End();



			button1.Text = "You clicked me";
		}

	}
}

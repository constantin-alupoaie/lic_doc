require "./converter"

cvt = Converter.new

cvt.convert {
	:ipath =>"../chapter3/*.png",
	:opath =>"../processed/chapter3/",
	:size =>"100x200"
}
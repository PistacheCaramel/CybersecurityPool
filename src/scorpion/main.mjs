import exifr from 'exifr';
import sharp from 'sharp';

async function extractEXIFmetadata(file)
{
		try {
			let metadata;
			metadata = await exifr.parse(file);
			console.log(metadata);
		} catch (error) {
			console.log("EXIF error:", error);
		}
}
 async function extractOtherMetadata(file)
{
	try {
		let metadata;
		metadata = await sharp(file).metadata();
		console.log(metadata);
	} catch (error) {
		console.log("Sharp error:", error);
	}

}

async function extractMetadatas(file)
{
	console.log("------EXIF-------");
	await extractEXIFmetadata(file);
	console.log("------SHARP------");
	await extractOtherMetadata(file);
}
const args = process.argv.slice(2);
 args.forEach((file) =>
{
	extractMetadatas(file);
}
 );
console.log('Arguments passés :', args);

